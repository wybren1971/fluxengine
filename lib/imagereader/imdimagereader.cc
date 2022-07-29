#include "globals.h"
#include "flags.h"
#include "sector.h"
#include "imagereader/imagereader.h"
#include "image.h"
#include "proto.h"
#include "logger.h"
#include "mapper.h"
#include "lib/config.pb.h"
#include "fmt/format.h"
#include <algorithm>
#include <iostream>
#include <fstream>

static unsigned getModulationandSpeed(uint8_t flags, bool *fm)
{
    switch (flags)
        {
            case 0: /* 500 kbps FM */
                //clockRateKhz.setDefaultValue(250);
                *fm = true;
                return 500;
                break;

            case 1: /* 300 kbps FM */
                *fm  = true;
                return 300;
                
                break;

            case 2: /* 250 kbps FM */
                *fm  = true;
                return 250;
                break;

            case 3: /* 500 kbps MFM */
                *fm  = false;
                return 500;
                break;

            case 4: /* 300 kbps MFM */
                *fm  = false;
                return 300;
                break;

            case 5: /* 250 kbps MFM */
                *fm  = false;
                return 250;
                break;

            default:
                Error() << fmt::format("IMD: don't understand IMD disks with this modulation and speed {}", flags);
                throw 0;
        }
}

struct TrackHeader
{
    uint8_t ModeValue;
    uint8_t track;
    uint8_t Head;
    uint8_t numSectors;
    uint8_t SectorSize;
};

static unsigned getSectorSize(uint8_t flags)
{
    switch (flags)
    {
        case 0: 
			return 128;
			break;
        case 1: 
			return 256;
			break;
        case 2: 
			return 512;
			break;
        case 3: 
			return 1024;
			break;
        case 4: 
			return 2048;
			break;
        case 5: 
			return 4096;
			break;
        case 6: 
			return 8192;
			break;
		default:
	    	Error() << "not reachable";
			throw 0;
	}
}


#define SEC_CYL_MAP_FLAG  0x80 
#define SEC_HEAD_MAP_FLAG 0x40
#define HEAD_MASK         0x3F
#define END_OF_FILE       0x1A


class IMDImageReader : public ImageReader
{
public:
    IMDImageReader(const ImageReaderProto& config): ImageReader(config) {}

    std::unique_ptr<Image> readImage()
    /*
    IMAGE FILE FORMAT
    The overall layout of an ImageDisk .IMD image file is:
    IMD v.vv: dd/mm/yyyy hh:mm:ss
    Comment (ASCII only - unlimited size)
    1A byte - ASCII EOF character
    - For each track on the disk:
    1 byte Mode value                           see getModulationspeed for definition       
    1 byte Track
    1 byte Head
    1 byte number of sectors in track           
    1 byte sector size                          see getsectorsize for definition
    sector numbering map
    sector track map (optional)              definied in high byte of head (since head is 0 or 1)
    sector head map (optional)                  definied in high byte of head (since head is 0 or 1)
    sector data records
    <End of file>
    */
    {
        //Read File
        std::ifstream inputFile(_config.filename(), std::ios::in | std::ios::binary);
        if (!inputFile.is_open())
            Error() << "IMD: cannot open input file";
        //define some variables
        bool fm = false;   //define coding just to show in comment for setting the right write parameters
        inputFile.seekg(0, inputFile.end);
        int inputFileSize = inputFile.tellg();  // determine filesize
        inputFile.seekg(0, inputFile.beg);
        Bytes data;
        data.writer() += inputFile;
        ByteReader br(data);
        std::unique_ptr<Image> image(new Image);
        TrackHeader header = {0, 0, 0, 0, 0};
        TrackHeader previousheader = {0, 0, 0, 0, 0};

        unsigned n = 0;
        unsigned headerPtr = 0;
        unsigned Modulation_Speed = 0;
        unsigned sectorSize = 0;
    	std::string sector_skew;

        int b;  
        std::string comment;
		bool blnOptionalCylinderMap = false;
		bool blnOptionalHeadMap = false;
		int trackSectorSize = -1;
		// Read comment
		comment.clear();
		while ((b = br.read_8()) != EOF && b != END_OF_FILE)
		{
			comment.push_back(b);
			n++;
		}        
		headerPtr = n; //set pointer to after comment
		Logger() 	<< "Comment in IMD file:"
					<< fmt::format("{}",
					comment);

        for (;;)
        {
            if (headerPtr >= inputFileSize-1)
            {
                break;
            }
            //first read header
            header.ModeValue = br.read_8();
            headerPtr++;
            Modulation_Speed = getModulationandSpeed(header.ModeValue, &fm);
            header.track = br.read_8();
            headerPtr++;
            header.Head = br.read_8();
            headerPtr++;
            header.numSectors = br.read_8();
            headerPtr++;
            header.SectorSize = br.read_8();
            headerPtr++;
            sectorSize = getSectorSize(header.SectorSize);

			unsigned optionalsector_map[header.numSectors];
			//The Sector Cylinder Map has one entry for each sector, and contains the logical Cylinder ID for the corresponding sector in the Sector Numbering Map.
			if (header.Head & SEC_CYL_MAP_FLAG) 
			{
				//Read optional cylinder map
				for (b = 0;  b < header.numSectors; b++)
				{
					optionalsector_map[b] = br.read_8();
					headerPtr++;
				}
				blnOptionalCylinderMap = true;				//set bool so we know there is an optional cylinder map
				header.Head = header.Head^SEC_CYL_MAP_FLAG; //remove flag 10000001 ^ 10000000 = 00000001 and 10000000 ^ 10000000 = 00000000 
			}
			//Read optional sector head map
			//The Sector Head Map has one entry for each sector, and contains the logical Head ID for the corresponding sector in the Sector Numbering Map.
			unsigned optionalhead_map[header.numSectors];
			if (header.Head & SEC_HEAD_MAP_FLAG) 
			{
				//Read optional sector head map 
				for (b = 0;  b < header.numSectors; b++)
				{
					optionalhead_map[b] = br.read_8();
					headerPtr++;
				}
				blnOptionalHeadMap = true;					//set bool so we know there is an optional head map
				header.Head = header.Head^SEC_HEAD_MAP_FLAG; //remove flag 01000001 ^ 01000001 = 00000001 and 01000000 ^ 0100000 = 00000000 for writing sector head later
			}            
            //read sector numbering map
			sector_skew.clear();
			bool blnBase0 = false; //check what first start number of the sector is. Fluxengine expects 1.
			for (b = 0;  b < header.numSectors; b++)
			{	
				uint8_t t;
				t = br.read_8();
				if (t == 0x00) blnBase0 = true;
				if (blnBase0)
				{
					t=t+1;
				}
				sector_skew.push_back(t);
				headerPtr++;
            }

		    auto ibm = config.mutable_encoder()->mutable_ibm();
           
            auto trackdata = ibm->add_trackdata();
            trackdata->set_target_clock_period_us(1e3 / Modulation_Speed);
            trackdata->set_target_rotational_period_ms(200);
			if (trackSectorSize < 0)
			{
				trackSectorSize = sectorSize;
				// this is the first sector we've read, use it settings for
				// per-track data
				trackdata->set_track(header.track);
				trackdata->set_head(header.Head);
				trackdata->set_sector_size(sectorSize);
				trackdata->set_use_fm(fm);
			}
			else if (trackSectorSize != sectorSize)
			{
				Error() << "IMD: multiple sector sizes per track are "
							"currently unsupported";
			}
            auto sectors = trackdata->mutable_sectors();
            
            //read the sectors
            for (int s = 0; s < header.numSectors; s++)
            {
                Bytes sectordata;
   				Bytes compressed(sectorSize);
				int SectorID;
				SectorID = sector_skew[s];
                const auto& sector = image->put(header.track, header.Head, SectorID);
				sector->logicalSector = SectorID;
                //read the status of the sector
                unsigned int Status_Sector = br.read_8();
                headerPtr++;

                switch (Status_Sector)
                {
				/*fluxengine knows of a few sector statussen but not all of the statussen in IMD.
				*  // the statussen are in sector.h. Translation to fluxengine is as follows:
				*	Statussen fluxengine							|	Status IMD		
				*--------------------------------------------------------------------------------------------------------------------
				*  	OK,												|	1, 2 (Normal data: (Sector Size) of (compressed) bytes follow)
				*	BAD_CHECKSUM,									|	5, 6, 7, 8
				*	MISSING,	  sector not found					|	0 (Sector data unavailable - could not be read)
				*	DATA_MISSING, sector present but no data found	|	3, 4
				*	CONFLICT,										|
				*	INTERNAL_ERROR									|
				*/
					case 0: /* Sector data unavailable - could not be read */

						sector->status = Sector::MISSING;
						break;

					case 1: /* Normal data: (Sector Size) bytes follow */
						sectordata = br.read(sectorSize);
						headerPtr += sectorSize;
						sector->data.writer().append(sectordata);
						sector->status = Sector::OK;
						break;

					case 2: /* Compressed: All bytes in sector have same value (xx) */
						compressed[0] = br.read_8();
						headerPtr++;
						for (int k = 1; k < sectorSize; k++)
						{
							//fill data till sector is full
							br.seek(headerPtr);
							compressed[k] = br.read_8();
						}
						sector->data.writer().append(compressed);
						sector->status = Sector::OK;
						break;

					case 3: /* Normal data with "Deleted-Data address mark" */
						sector->status = Sector::DATA_MISSING;
						sectordata = br.read(sectorSize);
						headerPtr += sectorSize;
						sector->data.writer().append(sectordata);						
						break;

					case 4: /* Compressed with "Deleted-Data address mark"*/
						compressed[0] = br.read_8();
						headerPtr++;
						for (int k = 1; k < sectorSize; k++)
						{
							//fill data till sector is full
							br.seek(headerPtr);
							compressed[k] = br.read_8();
						}
						sector->data.writer().append(compressed);
						sector->status = Sector::DATA_MISSING;
						break;

					case 5: /* Normal data read with data error*/
						sectordata = br.read(sectorSize);
						headerPtr += sectorSize;
						sector->status = Sector::BAD_CHECKSUM;
						sector->data.writer().append(sectordata);						
						break;

					case 6: /* Compressed read with data error*/
						compressed[0] = br.read_8();
						headerPtr++;
						for (int k = 1; k < sectorSize; k++)
						{
							//fill data till sector is full
							br.seek(headerPtr);
							compressed[k] = br.read_8();
						}
						sector->data.writer().append(compressed);
						sector->status = Sector::BAD_CHECKSUM;
						break;

					case 7: /* Deleted data read with data error*/
						sectordata = br.read(sectorSize);
						headerPtr += sectorSize;
						sector->status = Sector::BAD_CHECKSUM;
						sector->data.writer().append(sectordata);						
						break;

					case 8: /* Compressed, Deleted read with data error*/
						compressed[0] = br.read_8();
						headerPtr++;
						for (int k = 1; k < sectorSize; k++)
						{
							//fill data till sector is full
							br.seek(headerPtr);
							compressed[k] = br.read_8();
						}
						sector->data.writer().append(compressed);
						sector->status = Sector::BAD_CHECKSUM;
						break;

					default:
						Error() << fmt::format("IMD: Don't understand IMD files with sector status {}, track {}, sector {}", Status_Sector, header.track, s);
				}		
				if (blnOptionalCylinderMap) //there was een optional cylinder map. write it to the sector
				//The Sector Cylinder Map has one entry for each sector, and contains the logical Cylinder ID for the corresponding sector in the Sector Numbering Map.
				{
					sector->physicalTrack = Mapper::remapTrackLogicalToPhysical(header.track);
					sector->logicalTrack = optionalsector_map[s];
					blnOptionalCylinderMap = false;
				}
				else 
				{
					sector->logicalTrack = header.track;
                    sector->physicalTrack = Mapper::remapTrackLogicalToPhysical(header.track);
				}
				if (blnOptionalHeadMap) //there was een optional head map. write it to the sector
				//The Sector Head Map has one entry for each sector, and contains the logical Head ID for the corresponding sector in the Sector Numbering Map.
				{
					sector->physicalHead = header.Head;
					sector->logicalSide = optionalhead_map[s];
					blnOptionalHeadMap = false;
				}
				else 
				{
					sector->logicalSide = header.Head;
                    sector->physicalHead = header.Head;
				}
            }

        }
        
        if (config.encoder().format_case() != EncoderProto::FormatCase::FORMAT_NOT_SET)
            Logger() << "IMD: overriding configured format";


        image->calculateSize();
        const Geometry& geometry = image->getGeometry();
       	size_t headSize = ((header.numSectors) * (sectorSize));
    	size_t trackSize = (headSize * (header.Head + 1));


    	Logger() << "IMD: read "
				<< fmt::format("{} tracks, {} heads; {}; {} kbps; {} sectors; sectorsize {}; {} kB total.",
				header.track + 1, header.Head + 1,
				fm ? "FM" : "MFM",
				Modulation_Speed, header.numSectors, sectorSize, (header.track+1) * trackSize / 1024);

        if (!config.has_heads())
        {
            auto* heads = config.mutable_heads();
            heads->set_start(0);
            heads->set_end(geometry.numSides - 1);
        }

        if (!config.has_tracks())
        {
            auto* tracks = config.mutable_tracks();
            tracks->set_start(0);
            tracks->set_end(geometry.numTracks - 1);
        }

        return image;

    }
};

std::unique_ptr<ImageReader> ImageReader::createIMDImageReader(
    const ImageReaderProto& config)
{
    return std::unique_ptr<ImageReader>(new IMDImageReader(config));
}

// vim: ts=4 sw=4 et
