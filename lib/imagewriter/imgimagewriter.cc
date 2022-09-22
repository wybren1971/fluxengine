#include "globals.h"
#include "flags.h"
#include "sector.h"
#include "imagewriter/imagewriter.h"
#include "image.h"
#include "lib/proto.h"
#include "lib/config.pb.h"
#include "lib/layout.h"
#include "lib/layout.pb.h"
#include "fmt/format.h"
#include "logger.h"
#include <algorithm>
#include <iostream>
#include <fstream>

class ImgImageWriter : public ImageWriter
{
public:
    ImgImageWriter(const ImageWriterProto& config): ImageWriter(config) {}

    void writeImage(const Image& image)
    {
        const Geometry geometry = image.getGeometry();

        auto& layout = config.layout();
        int tracks = layout.has_tracks() ? layout.tracks() : geometry.numTracks;
        int sides = layout.has_sides() ? layout.sides() : geometry.numSides;

        std::ofstream outputFile(
            _config.filename(), std::ios::out | std::ios::binary);
        if (!outputFile.is_open())
            Error() << "cannot open output file";

        for (const auto& p : Layout::getTrackOrdering(tracks, sides))
        {
            int track = p.first;
            int side = p.second;

            auto trackLayout = Layout::getLayoutOfTrack(track, side);
            for (int sectorId : trackLayout->logicalSectorOrder)
            {
                const auto& sector = image.get(track, side, sectorId);
                if (sector)
                    sector->data.slice(0, trackLayout->sectorSize).writeTo(outputFile);
                else
                    outputFile.seekp(trackLayout->sectorSize, std::ios::cur);
            }
        }

        Logger() << fmt::format("IMG: wrote {} tracks, {} sides, {} kB total to {}",
            tracks,
            sides,
            outputFile.tellp() / 1024,
			_config.filename());
    }
};

std::unique_ptr<ImageWriter> ImageWriter::createImgImageWriter(
    const ImageWriterProto& config)
{
    return std::unique_ptr<ImageWriter>(new ImgImageWriter(config));
}
