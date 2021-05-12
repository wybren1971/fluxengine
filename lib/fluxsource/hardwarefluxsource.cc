#include "globals.h"
#include "flags.h"
#include "fluxmap.h"
#include "usb/usb.h"
#include "fluxsource/fluxsource.h"
#include "flaggroups/fluxsourcesink.h"
#include "fmt/format.h"

FlagGroup hardwareFluxSourceFlags = {
	&fluxSourceSinkFlags,
	&usbFlags
};

static DoubleFlag revolutions(
    { "--revolutions" },
    "read this many revolutions of the disk",
    1.25);

static BoolFlag synced(
    { "--sync-with-index" },
    "whether to wait for an index pulse before started to read",
    false);

static IntFlag indexMode(
    { "--index-mode" },
    "index pulse source (0=drive, 1=300 RPM fake source, 2=360 RPM fake source",
    0);

static IntFlag hardSectorCount(
    { "--hard-sector-count" },
    "number of hard sectors on the disk (0=soft sectors)",
    0);

class HardwareFluxSource : public FluxSource
{
public:
    HardwareFluxSource(unsigned drive):
        _drive(drive)
    {
        usbSetDrive(_drive, fluxSourceSinkHighDensity, indexMode);
        std::cerr << "Measuring rotational speed... " << std::flush;
        _oneRevolution = usbGetRotationalPeriod(hardSectorCount);
	if (hardSectorCount != 0)
		_hardSectorThreshold = _oneRevolution * 3 / (4 * hardSectorCount);
	else
		_hardSectorThreshold = 0;
        std::cerr << fmt::format("{}ms\n", _oneRevolution / 1e6);
    }

    ~HardwareFluxSource()
    {
    }

public:
    std::unique_ptr<Fluxmap> readFlux(int track, int side)
    {
        usbSetDrive(_drive, fluxSourceSinkHighDensity, indexMode);
		if (fluxSourceSinkFortyTrack)
		{
			if (track & 1)
				Error() << "cannot read from odd physical tracks in 40-track mode";
			usbSeek(track / 2);
		}
		else
			usbSeek(track);

        Bytes data = usbRead(
			side, synced, revolutions * _oneRevolution, _hardSectorThreshold);
        auto fluxmap = std::make_unique<Fluxmap>();
        fluxmap->appendBytes(data);
        return fluxmap;
    }

    void recalibrate()
    {
        usbRecalibrate();
    }

    bool retryable()
    {
        return true;
    }

private:
    unsigned _drive;
    unsigned _revolutions;
    nanoseconds_t _oneRevolution;
    nanoseconds_t _hardSectorThreshold;
};

void setHardwareFluxSourceRevolutions(double revolutions)
{
    ::revolutions.setDefaultValue(revolutions);
}

void setHardwareFluxSourceSynced(bool synced)
{
    ::synced.setDefaultValue(synced);
}

void setHardwareFluxSourceHardSectorCount(int sectorCount)
{
    ::hardSectorCount.setDefaultValue(sectorCount);
}

std::unique_ptr<FluxSource> FluxSource::createHardwareFluxSource(unsigned drive)
{
    return std::unique_ptr<FluxSource>(new HardwareFluxSource(drive));
}



