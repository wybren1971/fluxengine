#include "globals.h"
#include "flags.h"
#include "sector.h"
#include "imagewriter/imagewriter.h"
#include "image.h"
#include "lib/config.pb.h"
#include "fmt/format.h"
#include <algorithm>
#include <iostream>
#include <fstream>

class ImgImageWriter : public ImageWriter
{
public:
	ImgImageWriter(const ImageWriterProto& config):
		ImageWriter(config)
	{}

	void writeImage(const Image& image)
	{
		const Geometry geometry = image.getGeometry();

		int tracks = _config.img().has_tracks() ? _config.img().tracks() : geometry.numTracks;
		int sides = _config.img().has_sides() ? _config.img().sides() : geometry.numSides;

		std::ofstream outputFile(_config.filename(), std::ios::out | std::ios::binary);
		if (!outputFile.is_open())
			Error() << "cannot open output file";

		for (int track = 0; track < tracks; track++)
		{
			for (int side = 0; side < sides; side++)
			{
				ImgInputOutputProto::TrackdataProto trackdata;
				getTrackFormat(trackdata, track, side);

				auto sectors = getSectors(trackdata);
				if (sectors.empty())
				{
					int maxSector = geometry.firstSector + geometry.numSectors - 1;
					for (int i=geometry.firstSector; i<=maxSector; i++)
						sectors.push_back(i);
				}

				int sectorSize = trackdata.has_sector_size() ? trackdata.sector_size() : geometry.sectorSize;

				for (int sectorId : sectors)
				{
					const auto& sector = image.get(track, side, sectorId);
					if (sector)
						sector->data.slice(0, sectorSize).writeTo(outputFile);
					else
						outputFile.seekp(sectorSize, std::ios::cur);
				}
			}
		}

		std::cout << fmt::format("wrote {} tracks, {} sides, {} kB total\n",
						tracks, sides,
						outputFile.tellp() / 1024);
	}

private:
	void getTrackFormat(ImgInputOutputProto::TrackdataProto& trackdata, unsigned track, unsigned side)
	{
		trackdata.Clear();
		for (const ImgInputOutputProto::TrackdataProto& f : _config.img().trackdata())
		{
			if (f.has_track() && (f.track() != track))
				continue;
			if (f.has_side() && (f.side() != side))
				continue;

			trackdata.MergeFrom(f);
		}
	}

	std::vector<unsigned> getSectors(const ImgInputOutputProto::TrackdataProto& trackdata)
	{
		std::vector<unsigned> sectors;
		switch (trackdata.sectors_oneof_case())
		{
			case ImgInputOutputProto::TrackdataProto::SectorsOneofCase::kSectors:
			{
				for (int sectorId : trackdata.sectors().sector())
					sectors.push_back(sectorId);
				break;
			}

			case ImgInputOutputProto::TrackdataProto::SectorsOneofCase::kSectorRange:
			{
				int sectorId = trackdata.sector_range().start_sector();
				for (int i=0; i<trackdata.sector_range().sector_count(); i++)
					sectors.push_back(sectorId + i);
				break;
			}
		}
		return sectors;
	}
};

std::unique_ptr<ImageWriter> ImageWriter::createImgImageWriter(
	const ImageWriterProto& config)
{
    return std::unique_ptr<ImageWriter>(new ImgImageWriter(config));
}
