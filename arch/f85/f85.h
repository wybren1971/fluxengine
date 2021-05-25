#ifndef F85_H
#define F85_H

#define F85_SECTOR_RECORD 0xffffce /* 1111 1111 1111 1111 1100 1110 */
#define F85_DATA_RECORD 0xffffcb /* 1111 1111 1111 1111 1100 1101 */
#define F85_SECTOR_LENGTH    512

class Sector;
class Fluxmap;
class F85DecoderProto;

class DurangoF85Decoder : public AbstractDecoder
{
public:
	DurangoF85Decoder(const F85DecoderProto&) {}
    virtual ~DurangoF85Decoder() {}

    RecordType advanceToNextRecord();
    void decodeSectorRecord();
    void decodeDataRecord();
};

#endif
