#include "globals.h"
#include "flags.h"
#include "dataspec.h"
#include "sector.h"
#include "sectorset.h"
#include "imagereader/imagereader.h"
#include "fmt/format.h"
#include <algorithm>
#include <iostream>
#include <fstream>

class ImgImageReader : public ImageReader
{
public:
	ImgImageReader(const ImageSpec& spec):
		ImageReader(spec)
	{}

	SectorSet readImage()
	{
        std::ifstream inputFile(spec.filename, std::ios::in | std::ios::binary);
        if (!inputFile.is_open())
            Error() << "cannot open input file";

        size_t headSize = spec.sectors * spec.bytes;
        size_t trackSize = headSize * spec.heads;

        std::cout << fmt::format("reading {} tracks, {} heads, {} sectors, {} bytes per sector, {} kB total",
                        spec.cylinders, spec.heads,
                        spec.sectors, spec.bytes,
                        spec.cylinders * trackSize / 1024)
                << std::endl;
		if ((spec.physicalOffset != 0) || (spec.physicalStep != 1))
			std::cout << fmt::format("logical to physical track mapping: physical = logical*{} + {}\n",
				spec.physicalStep, spec.physicalOffset);

        SectorSet sectors;
        for (int track = 0; track < spec.cylinders; track++)
        {
            for (int head = 0; head < spec.heads; head++)
            {
                for (int sectorId = 0; sectorId < spec.sectors; sectorId++)
                {
                    inputFile.seekg(track*trackSize + head*headSize + sectorId*spec.bytes, std::ios::beg);

                    Bytes data(spec.bytes);
                    inputFile.read((char*) data.begin(), spec.bytes);

					int physicalTrack = track*spec.physicalStep + spec.physicalOffset;
                    std::unique_ptr<Sector>& sector = sectors.get(physicalTrack, head, sectorId);
                    sector.reset(new Sector);
                    sector->status = Sector::OK;
                    sector->logicalTrack = track;
					sector->physicalTrack = physicalTrack;
                    sector->logicalSide = sector->physicalSide = head;
                    sector->logicalSector = sectorId;
                    sector->data = data;
                }
            }
        }
        return sectors;
	}
};

std::unique_ptr<ImageReader> ImageReader::createImgImageReader(
	const ImageSpec& spec)
{
    return std::unique_ptr<ImageReader>(new ImgImageReader(spec));
}

