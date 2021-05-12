#include "globals.h"
#include "flags.h"
#include "fluxmap.h"
#include "writer.h"
#include "sql.h"
#include "protocol.h"
#include "usb/usb.h"
#include "dataspec.h"
#include "encoders/encoders.h"
#include "fluxsource/fluxsource.h"
#include "fluxsink/fluxsink.h"
#include "imagereader/imagereader.h"
#include "fmt/format.h"
#include "record.h"
#include "sector.h"
#include "sectorset.h"

FlagGroup writerFlags { &hardwareFluxSourceFlags, &sqliteFluxSinkFlags, &hardwareFluxSinkFlags };

static DataSpecFlag dest(
    { "--dest", "-d" },
    "destination for data",
    ":d=0:t=0-79:s=0-1");

static DataSpecFlag input(
    { "--input", "-i" },
    "input image file to read from",
    "");

static sqlite3* outdb;

void setWriterDefaultDest(const std::string& dest)
{
    ::dest.set(dest);
}

void setWriterDefaultInput(const std::string& input)
{
    ::input.set(input);
}

void setWriterHardSectorCount(int sectorCount)
{
	setHardwareFluxSinkHardSectorCount(sectorCount);
}

static SectorSet readSectorsFromFile(const ImageSpec& spec)
{
	return ImageReader::create(spec)->readImage();
}

void writeTracks(
	const std::function<std::unique_ptr<Fluxmap>(int track, int side)> producer)
{
    const FluxSpec spec(dest);

    std::cout << "Writing to: " << dest << std::endl;

	std::shared_ptr<FluxSink> fluxSink = FluxSink::create(spec);

    for (const auto& location : spec.locations)
    {
        std::cout << fmt::format("{0:>3}.{1}: ", location.track, location.side) << std::flush;
        std::unique_ptr<Fluxmap> fluxmap = producer(location.track, location.side);
        if (!fluxmap)
        {
			/* Erase this track rather than writing. */

            fluxmap.reset(new Fluxmap());
			fluxSink->writeFlux(location.track, location.side, *fluxmap);
			std::cout << "erased\n";
        }
		else
		{
			/* Precompensation actually seems to make things worse, so let's leave
				* it disabled for now. */
			//fluxmap->precompensate(PRECOMPENSATION_THRESHOLD_TICKS, 2);
			fluxSink->writeFlux(location.track, location.side, *fluxmap);
			std::cout << fmt::format(
				"{0} ms in {1} bytes", int(fluxmap->duration()/1e6), fluxmap->bytes()) << std::endl;
		}
    }
}

void fillBitmapTo(std::vector<bool>& bitmap,
	unsigned& cursor, unsigned terminateAt,
	const std::vector<bool>& pattern)
{
	while (cursor < terminateAt)
	{
		for (bool b : pattern)
		{
			if (cursor < bitmap.size())
				bitmap[cursor++] = b;
		}
	}
}

void writeDiskCommand(AbstractEncoder& encoder)
{
    const ImageSpec spec(input);
	SectorSet allSectors = readSectorsFromFile(spec);
	writeTracks(
		[&](int track, int side) -> std::unique_ptr<Fluxmap>
		{
			return encoder.encode(track, side, allSectors);
		}
	);
}
