#ifndef C64_H
#define C64_H

#include "decoders/decoders.h"
#include "encoders/encoders.h"

#define C64_SECTOR_RECORD    0xffd49
#define C64_DATA_RECORD      0xffd57
#define C64_SECTOR_LENGTH    256

/* Source: http://www.unusedino.de/ec64/technical/formats/g64.html 
   1. Header sync       FF FF FF FF FF (40 'on' bits, not GCR)
   2. Header info       52 54 B5 29 4B 7A 5E 95 55 55 (10 GCR bytes)
   3. Header gap        55 55 55 55 55 55 55 55 55 (9 bytes, never read)
   4. Data sync         FF FF FF FF FF (40 'on' bits, not GCR)
   5. Data block        55...4A (325 GCR bytes)
   6. Inter-sector gap  55 55 55 55...55 55 (4 to 12 bytes, never read)
   1. Header sync       (SYNC for the next sector)
*/
#define C64_HEADER_DATA_SYNC        0xFF
#define C64_HEADER_BLOCK_ID         0x08
#define C64_DATA_BLOCK_ID           0x07
#define C64_HEADER_GAP              0x55
#define C64_INTER_SECTOR_GAP        0x55
#define C64_PADDING                 0x0F

#define C64_TRACKS_PER_DISK         40
#define C64_BAM_TRACK               17


class Sector;
class Fluxmap;
class Commodore64DecoderProto;
class Commodore64EncoderProto;

class Commodore64Decoder : public AbstractDecoder
{
public:
	Commodore64Decoder(const Commodore64DecoderProto&) {}
    virtual ~Commodore64Decoder() {}

    RecordType advanceToNextRecord();
    void decodeSectorRecord();
    void decodeDataRecord();
};

class Commodore64Encoder : public AbstractEncoder
{
public:
	Commodore64Encoder(const Commodore64EncoderProto& config):
		_config(config)
	{}

	virtual ~Commodore64Encoder() {}

public:
    std::unique_ptr<Fluxmap> encode(int physicalTrack, int physicalSide, const SectorSet& allSectors);

private:
	const Commodore64EncoderProto& _config;
};

#endif
