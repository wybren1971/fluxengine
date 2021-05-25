#include "globals.h"
#include "flags.h"
#include "sector.h"
#include "sectorset.h"
#include "imagewriter/imagewriter.h"
#include "fmt/format.h"
#include "ldbs.h"
#include "lib/config.pb.h"
#include <algorithm>
#include <iostream>
#include <fstream>

static const char LABEL[] = "FluxEngine image";

static void write_and_update_checksum(ByteWriter& bw, uint32_t& checksum, const Bytes& data)
{
	ByteReader br(data);
	while (!br.eof())
	{
		uint32_t i = br.read_be16();
		checksum += i;
		checksum = (checksum >> 1) | (checksum << 31);
		bw.write_be16(i);
	}
}

class DiskCopyImageWriter : public ImageWriter
{
public:
	DiskCopyImageWriter(const ImageWriterProto& config):
		ImageWriter(config)
	{}

	void writeImage(const SectorSet& sectors)
	{
		unsigned numCylinders;
		unsigned numHeads;
		unsigned numSectors;
		unsigned numBytes;
		sectors.calculateSize(numCylinders, numHeads, numSectors, numBytes);

		bool mfm = false;

		switch (numBytes)
		{
			case 524:
				/* GCR disk */
				break;

			case 512:
				/* MFM disk */
				mfm = true;
				break;

			default:
				Error() << "this image is not compatible with the DiskCopy 4.2 format";
		}

		std::cout << "writing DiskCopy 4.2 image\n"
		          << fmt::format("{} tracks, {} heads, {} sectors, {} bytes per sector; {}\n",
				  		numCylinders, numHeads, numSectors, numBytes,
						mfm ? "MFM" : "GCR");

		auto sectors_per_track = [&](int track) -> int
		{
			if (mfm)
				return numSectors;

			if (track < 16)
				return 12;
			if (track < 32)
				return 11;
			if (track < 48)
				return 10;
			if (track < 64)
				return 9;
			return 8;
		};

		Bytes image;
		ByteWriter bw(image);

		/* Write the actual sectr data. */

		uint32_t dataChecksum = 0;
		uint32_t tagChecksum = 0;
		uint32_t offset = 0x54;
		uint32_t sectorDataStart = offset;
		for (int track = 0; track < numCylinders; track++)
		{
			for (int head = 0; head < numHeads; head++)
			{
				int sectorCount = sectors_per_track(track);
				for (int sectorId = 0; sectorId < sectorCount; sectorId++)
				{
					const auto& sector = sectors.get(track, head, sectorId);
					if (sector)
					{
						bw.seek(offset);
						write_and_update_checksum(bw, dataChecksum, sector->data.slice(0, 512));
					}
					offset += 512;
				}
			}
		}
		uint32_t sectorDataEnd = offset;
		if (!mfm)
		{
			for (int track = 0; track < numCylinders; track++)
			{
				for (int head = 0; head < numHeads; head++)
				{
					int sectorCount = sectors_per_track(track);
					for (int sectorId = 0; sectorId < sectorCount; sectorId++)
					{
						const auto& sector = sectors.get(track, head, sectorId);
						if (sector)
						{
							bw.seek(offset);
							write_and_update_checksum(bw, tagChecksum, sector->data.slice(512, 12));
						}
						offset += 12;
					}
				}
			}
		}
		uint32_t tagDataEnd = offset;

		/* Write the header. */

		uint8_t encoding;
		uint8_t format;
		if (mfm)
		{
			format = 0x22;
			if (numSectors == 18)
				encoding = 3;
			else
				encoding = 2;
		}
		else
		{
			if (numHeads == 2)
			{
				encoding = 1;
				format = 0x22;
			}
			else
			{
				encoding = 0;
				format = 0x02;
			}
		}

		bw.seek(0);
		bw.write_8(sizeof(LABEL));
		bw.append(LABEL);
		bw.seek(0x40);
		bw.write_be32(sectorDataEnd - sectorDataStart); /* data size */
		bw.write_be32(tagDataEnd - sectorDataEnd); /* tag size */
		bw.write_be32(dataChecksum); /* data checksum */
		bw.write_be32(tagChecksum); /* tag checksum */
		bw.write_8(encoding); /* encoding */
		bw.write_8(format); /* format byte */
		bw.write_be16(0x0100); /* magic number */

		image.writeToFile(_config.filename());
    }
};

std::unique_ptr<ImageWriter> ImageWriter::createDiskCopyImageWriter(
	const ImageWriterProto& config)
{
    return std::unique_ptr<ImageWriter>(new DiskCopyImageWriter(config));
}


