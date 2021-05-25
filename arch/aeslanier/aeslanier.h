#ifndef AESLANIER_H
#define AESLANIER_H

#define AESLANIER_RECORD_SEPARATOR 0x55555122
#define AESLANIER_SECTOR_LENGTH    256
#define AESLANIER_RECORD_SIZE      (AESLANIER_SECTOR_LENGTH + 5)

class Sector;
class Fluxmap;
class AesLanierDecoderProto;

class AesLanierDecoder : public AbstractDecoder
{
public:
	AesLanierDecoder(const AesLanierDecoderProto&) {}
    virtual ~AesLanierDecoder() {}

    RecordType advanceToNextRecord();
    void decodeSectorRecord();
};

#endif
