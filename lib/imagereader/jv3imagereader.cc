#include "globals.h"
#include "flags.h"
#include "sector.h"
#include "sectorset.h"
#include "imagereader/imagereader.h"
#include "fmt/format.h"
#include "lib/config.pb.h"
#include <algorithm>
#include <iostream>
#include <fstream>

/* JV3 files are kinda weird. There's a fixed layout for up to 2901 sectors, which may appear
 * in any order, followed by the same again for more sectors. To find the second data block
 * you need to know the size of the first data block, which requires parsing it.
 *
 * https://www.tim-mann.org/trs80/dskconfig.html
 *
 * typedef struct {
 *   SectorHeader headers1[2901];
 *   unsigned char writeprot;
 *   unsigned char data1[];
 *   SectorHeader headers2[2901];
 *   unsigned char padding;
 *   unsigned char data2[];
 * } JV3;
 *
 * typedef struct {
 *   unsigned char track;
 *   unsigned char sector;
 *   unsigned char flags;
 * } SectorHeader;
 */

struct SectorHeader
{
	uint8_t track;
	uint8_t sector;
	uint8_t flags;
};

#define JV3_DENSITY     0x80  /* 1=dden, 0=sden */
#define JV3_DAM         0x60  /* data address mark code; see below */
#define JV3_SIDE        0x10  /* 0=side 0, 1=side 1 */
#define JV3_ERROR       0x08  /* 0=ok, 1=CRC error */
#define JV3_NONIBM      0x04  /* 0=normal, 1=short */
#define JV3_SIZE        0x03  /* in used sectors: 0=256,1=128,2=1024,3=512
                                 in free sectors: 0=512,1=1024,2=128,3=256 */

#define JV3_FREE        0xFF  /* in track and sector fields of free sectors */
#define JV3_FREEF       0xFC  /* in flags field, or'd with size code */

static unsigned getSectorSize(uint8_t flags)
{
	if ((flags & JV3_FREEF) == JV3_FREEF)
	{
		switch (flags & JV3_SIZE)
		{
			case 0: return 512;
			case 1: return 1024;
			case 2: return 128;
			case 3: return 256;
		}
	}
	else
	{
		switch (flags & JV3_SIZE)
		{
			case 0: return 256;
			case 1: return 128;
			case 2: return 1024;
			case 3: return 512;
		}
	}
	Error() << "not reachable";
}

class Jv3ImageReader : public ImageReader
{
public:
	Jv3ImageReader(const ImageReaderProto& config):
		ImageReader(config)
	{}

	SectorSet readImage()
	{
        std::ifstream inputFile(_config.filename(), std::ios::in | std::ios::binary);
        if (!inputFile.is_open())
            Error() << "cannot open input file";

		inputFile.seekg( 0, std::ios::end);
		unsigned inputFileSize = inputFile.tellg();
		unsigned headerPtr = 0;
		SectorSet sectors;
		for (;;)
		{
			unsigned dataPtr = headerPtr + 2901*3 + 1;
			if (dataPtr >= inputFileSize)
				break;

			for (unsigned i=0; i<2901; i++)
			{
				SectorHeader header = {0, 0, 0xff};
				inputFile.seekg(headerPtr);
				inputFile.read((char*) &header, 3);
				unsigned sectorSize = getSectorSize(header.flags);
				if ((header.flags & JV3_FREEF) != JV3_FREEF)
				{
					Bytes data(sectorSize);
					inputFile.seekg(dataPtr);
					inputFile.read((char*) data.begin(), sectorSize);

					unsigned head = !!(header.flags & JV3_SIDE);
                    std::unique_ptr<Sector>& sector = sectors.get(header.track, head, header.sector);
                    sector.reset(new Sector);
                    sector->status = Sector::OK;
                    sector->logicalTrack = sector->physicalTrack = header.track;
                    sector->logicalSide = sector->physicalSide = head;
                    sector->logicalSector = header.sector;
                    sector->data = data;
				}

				headerPtr += 3;
				dataPtr += sectorSize;
			}

			/* dataPtr is now pointing at the beginning of the next chunk. */

			headerPtr = dataPtr;
		}

        return sectors;
	}
};

std::unique_ptr<ImageReader> ImageReader::createJv3ImageReader(const ImageReaderProto& config)
{
    return std::unique_ptr<ImageReader>(new Jv3ImageReader(config));
}


