#include "globals.h"
#include "fluxmap.h"
#include "lib/fluxsource/fluxsource.pb.h"
#include "fluxsource/fluxsource.h"
#include "proto.h"
#include "fmt/format.h"
#include <fstream>

struct CwfHeader
{
    char file_id[4];      // file ID - almost always "CWSF"
    uint8_t creator;      // usually just the CW_TYPE
    uint8_t file_type;    // indexed, etc.?
    uint8_t version;      // version of this file
    uint8_t clock_rate;   // clock rate used: 0, 1, 2 (2 = 28MHz)
    uint8_t drive_type;   // type of drive
    uint8_t cylinders;    // number of cylinders
    uint8_t sides;        // number of sides
    uint8_t index_mark;   // nonzero if index marks are included
    uint8_t step;         // cylinder stepping interval
    uint8_t filler[15];   // reserved for expansion
    uint8_t comment[100]; // brief comment
};

struct CwfTrack
{
    uint8_t track;     // sequential
    uint8_t side;
    uint8_t unused[2];
    uint8_t length[4]; // little-endian
};

class CwfFluxSource : public FluxSource
{
public:
    CwfFluxSource(const CwfFluxSourceProto& config):
		_config(config)
    {
		_if.open(_config.filename(), std::ios::in | std::ios::binary);
		if (!_if.is_open())
			Error() << fmt::format("cannot open input file '{}': {}",
				_config.filename(), strerror(errno));

		_if.read((char*) &_header, sizeof(_header));
		check_for_error();

		if ((_header.file_id[0] != 'C')
				|| (_header.file_id[1] != 'W')
				|| (_header.file_id[2] != 'S')
				|| (_header.file_id[3] != 'F'))
			Error() << "input not a CWF file";

		switch (_header.clock_rate)
		{
			case 1: _clockRate = 14161000.0; break;
			case 2: _clockRate = 28322000.0; break;
			default:
				Error() << "unsupported clock rate";
		}

		std::cout << fmt::format("CWF {}x{} = {} cylinders, {} sides\n",
			_header.cylinders, _header.step, _header.cylinders*_header.step, _header.sides);
		std::cout << fmt::format("CWF sample clock rate: {} MHz\n", _clockRate / 1e6);

		int tracks = _header.cylinders*_header.sides;
		for (int i=0; i<tracks; i++)
		{
			CwfTrack trackheader;
			_if.read((char*) &trackheader, sizeof(trackheader));
			check_for_error();

			uint32_t length = Bytes(trackheader.length, 4).reader().read_le32() - sizeof(CwfTrack);
			unsigned track_number = trackheader.track * _header.step;

			off_t pos = _if.tellg();
			_trackOffsets[std::make_pair(track_number, trackheader.side)] = std::make_pair(pos, length);
			_if.seekg(pos + length);
		}
	}

public:
    std::unique_ptr<Fluxmap> readFlux(int track, int side)
    {
		const auto& p = _trackOffsets.find(std::make_pair(track, side));
		if (p == _trackOffsets.end())
			return std::unique_ptr<Fluxmap>();

		off_t pos = p->second.first;;
		size_t length = p->second.second;
		_if.seekg(pos);

		std::unique_ptr<Fluxmap> fluxmap(new Fluxmap);
		uint32_t pending = 0;
		bool oldindex = true;
		for (size_t cursor = 0; cursor < length; cursor++)
		{
			uint32_t b = _if.get();
			bool index = !!(b & 0x80);
			b &= 0x7f;
			if (b == 0x7f)
			{
				pending += 0x7f;
				continue;
			}
			b += pending;
			pending = 0;

			double interval_us = b * (1e6/_clockRate);
			fluxmap->appendInterval(interval_us / US_PER_TICK);
			fluxmap->appendPulse();

			if (index && !oldindex)
				fluxmap->appendIndex();
			oldindex = index;
		}
		check_for_error();

		return fluxmap;
    }

    void recalibrate() {}

private:
	void check_for_error()
	{
		if (_if.fail())
			Error() << fmt::format("SCP read I/O error: {}", strerror(errno));
	}

private:
    const CwfFluxSourceProto& _config;
	std::ifstream _if;
	CwfHeader _header;
	nanoseconds_t _clockRate;
	std::map<std::pair<int, int>, std::pair<off_t, size_t>> _trackOffsets;
};

std::unique_ptr<FluxSource> FluxSource::createCwfFluxSource(const CwfFluxSourceProto& config)
{
    return std::unique_ptr<FluxSource>(new CwfFluxSource(config));
}

#if 0
#include "globals.h"
#include "fluxmap.h"
#include "sql.h"
#include "bytes.h"
#include "protocol.h"

static std::ifstream inputFile;
static sqlite3* outputDb;
static CwfHeader header;
static double clockRate;

static void syntax()
{
    std::cout << "Syntax: fluxengine convert cwftoflux <cwffile> <fluxfile>\n";
    exit(0);
}

static void check_for_error()
{
    if (inputFile.fail())
        Error() << fmt::format("I/O error: {}", strerror(errno));
}

static void read_header()
{
}

static void read_track()
{
    CwfTrack trackheader;
    inputFile.read((char*) &trackheader, sizeof(trackheader));
    check_for_error();

    uint32_t length = Bytes(trackheader.length, 4).reader().read_le32() - sizeof(CwfTrack);
    unsigned track_number = trackheader.track * header.step;
    std::cout << fmt::format("{}.{}: {} input bytes; ", track_number, trackheader.side, length)
        << std::flush;

    std::vector<uint8_t> inputdata(length);
    inputFile.read((char*) &inputdata[0], length);
    check_for_error();


    std::cout << fmt::format(" {} ms in {} output bytes\n",
        fluxmap.duration() / 1e6, fluxmap.bytes());
    sqlWriteFlux(outputDb, track_number, trackheader.side, fluxmap);
}

int mainConvertCwfToFlux(int argc, const char* argv[])
{
    if (argc != 3)
        syntax();
    
    inputFile.open(argv[1], std::ios::in | std::ios::binary);
    if (!inputFile.is_open())
		Error() << fmt::format("cannot open input file '{}'", argv[1]);

    outputDb = sqlOpen(argv[2], SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE);
    sqlPrepareFlux(outputDb);
    sqlWriteIntProperty(outputDb, "version", FLUX_VERSION_CURRENT);
    sqlStmt(outputDb, "BEGIN;");

    read_header();
    inputFile.seekg(sizeof(header), std::ios::beg);
    for (unsigned i=0; i<(header.cylinders*header.sides); i++)
        read_track();

    sqlStmt(outputDb, "COMMIT;");
    sqlClose(outputDb);
    return 0;
}
#endif
