#include "globals.h"
#include "flags.h"
#include "usb/usb.h"
#include "fluxsource/fluxsource.h"
#include "fluxsink/fluxsink.h"
#include "reader.h"
#include "fluxmap.h"
#include "sql.h"
#include "decoders/decoders.h"
#include "sector.h"
#include "sectorset.h"
#include "record.h"
#include "bytes.h"
#include "decoders/rawbits.h"
#include "track.h"
#include "imagewriter/imagewriter.h"
#include "fmt/format.h"
#include "proto.h"
#include "lib/decoders/decoders.pb.h"
#include <iostream>
#include <fstream>

static std::unique_ptr<FluxSink> outputFluxSink;

void Track::readFluxmap()
{
	std::cout << fmt::format("{0:>3}.{1}: ", physicalTrack, physicalSide) << std::flush;
	fluxmap = fluxsource->readFlux(physicalTrack, physicalSide);
	if (!fluxmap)
		fluxmap.reset(new Fluxmap());
	std::cout << fmt::format(
		"{0} ms in {1} bytes\n",
            fluxmap->duration()/1e6,
            fluxmap->bytes());
	if (outputFluxSink)
		outputFluxSink->writeFlux(physicalTrack, physicalSide, *fluxmap);
}

static bool conflictable(Sector::Status status)
{
	return (status == Sector::OK) || (status == Sector::CONFLICT);
}

static void replace_sector(std::unique_ptr<Sector>& replacing, Sector& replacement)
{
	if (replacing && conflictable(replacing->status) && conflictable(replacement.status))
	{
		if (replacement.data != replacing->data)
		{
			std::cout << std::endl
						<< "       multiple conflicting copies of sector " << replacing->logicalSector
						<< " seen; ";
			replacing->status = Sector::CONFLICT;
			return;
		}
	}
	if (!replacing || ((replacing->status != Sector::OK) && (replacement.status == Sector::OK)))
	{
		if (!replacing)
			replacing.reset(new Sector);
		*replacing = replacement;
	}
}

void readDiskCommand(FluxSource& fluxsource, AbstractDecoder& decoder, ImageWriter& writer)
{
	if (config.decoder().has_copy_flux_to())
		outputFluxSink = FluxSink::create(config.decoder().copy_flux_to());

	bool failures = false;
	SectorSet allSectors;
	for (int cylinder : iterate(config.cylinders()))
	{
		for (int head : iterate(config.heads()))
		{
			auto track = std::make_unique<Track>(cylinder, head);
			track->fluxsource = &fluxsource;

			std::map<int, std::unique_ptr<Sector>> readSectors;
			for (int retry = config.decoder().retries(); retry >= 0; retry--)
			{
				track->readFluxmap();
				decoder.decodeToSectors(*track);

				std::cout << "       ";
					std::cout << fmt::format("{} records, {} sectors; ",
						track->rawrecords.size(),
						track->sectors.size());
					if (track->sectors.size() > 0)
						std::cout << fmt::format("{:.2f}us clock ({:.0f}kHz); ",
							track->sectors.begin()->clock / 1000.0,
							1000000.0 / track->sectors.begin()->clock);

					for (auto& sector : track->sectors)
					{
						auto& replacing = readSectors[sector.logicalSector];
						replace_sector(replacing, sector);
					}

					bool hasBadSectors = false;
					std::set<unsigned> requiredSectors = decoder.requiredSectors(*track);
					for (const auto& i : readSectors)
					{
						const auto& sector = i.second;
						requiredSectors.erase(sector->logicalSector);

						if (sector->status != Sector::OK)
						{
							std::cout << std::endl
									<< "       Failed to read sector " << sector->logicalSector
									<< " (" << Sector::statusToString((Sector::Status)sector->status) << "); ";
							hasBadSectors = true;
						}
					}
					for (unsigned logicalSector : requiredSectors)
					{
						std::cout << "\n"
								  << "       Required sector " << logicalSector << " missing; ";
						hasBadSectors = true;
					}

					if (hasBadSectors)
						failures = false;

					std::cout << std::endl
							<< "       ";

					if (!hasBadSectors)
						break;

				if (!track->fluxsource->retryable())
					break;
				if (retry == 0)
					std::cout << "giving up" << std::endl
							  << "       ";
				else
					std::cout << retry << " retries remaining" << std::endl;
			}

			if (config.decoder().dump_records())
			{
				std::cout << "\nRaw (undecoded) records follow:\n\n";
				for (auto& record : track->rawrecords)
				{
					std::cout << fmt::format("I+{:.2f}us with {:.2f}us clock\n",
								record.position.ns() / 1000.0, record.clock / 1000.0);
					hexdump(std::cout, record.data);
					std::cout << std::endl;
				}
			}

			if (config.decoder().dump_sectors())
			{
				std::cout << "\nDecoded sectors follow:\n\n";
				for (auto& sector : track->sectors)
				{
					std::cout << fmt::format("{}.{:02}.{:02}: I+{:.2f}us with {:.2f}us clock: status {}\n",
								sector.logicalTrack, sector.logicalSide, sector.logicalSector,
								sector.position.ns() / 1000.0, sector.clock / 1000.0,
								sector.status);
					hexdump(std::cout, sector.data);
					std::cout << std::endl;
				}
			}

			int size = 0;
			bool printedTrack = false;
			for (auto& i : readSectors)
			{
				auto& sector = i.second;
				if (sector)
				{
					if (!printedTrack)
					{
						std::cout << fmt::format("logical track {}.{}; ", sector->logicalTrack, sector->logicalSide);
						printedTrack = true;
					}

					size += sector->data.size();

					std::unique_ptr<Sector>& replacing = allSectors.get(sector->logicalTrack, sector->logicalSide, sector->logicalSector);
					replace_sector(replacing, *sector);
				}
			}
			std::cout << size << " bytes decoded." << std::endl;
		}
    }

	writer.printMap(allSectors);
	if (config.decoder().has_write_csv_to())
		writer.writeCsv(allSectors, config.decoder().write_csv_to());
	writer.writeImage(allSectors);

	if (failures)
		std::cerr << "Warning: some sectors could not be decoded." << std::endl;
}

void rawReadDiskCommand(FluxSource& fluxsource, FluxSink& fluxsink)
{
	for (int cylinder : iterate(config.cylinders()))
	{
		for (int head : iterate(config.heads()))
		{
			Track track(cylinder, head);
			track.fluxsource = &fluxsource;
			track.readFluxmap();

			fluxsink.writeFlux(cylinder, head, *(track.fluxmap));
		}
    }
}
