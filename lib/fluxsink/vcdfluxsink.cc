#include "globals.h"
#include "flags.h"
#include "fluxmap.h"
#include "sql.h"
#include "bytes.h"
#include "protocol.h"
#include "fluxsink/fluxsink.h"
#include "decoders/fluxmapreader.h"
#include "lib/fluxsink/fluxsink.pb.h"
#include "proto.h"
#include "fmt/format.h"
#include <fstream>
#include <sys/stat.h>
#include <sys/types.h>

class VcdFluxSink : public FluxSink
{
public:
	VcdFluxSink(const VcdFluxSinkProto& config):
		_config(config)
	{}

public:
	void writeFlux(int cylinder, int head, Fluxmap& fluxmap)
	{
		mkdir(_config.directory().c_str(), 0744);
		std::ofstream of(
			fmt::format("{}/c{:02d}.h{:01d}.vcd", _config.directory(), cylinder, head),
			std::ios::out | std::ios::binary);
		if (!of.is_open())
			Error() << "cannot open output file";

		of << "$timescale 1ns $end\n"
		   << "$var wire 1 i index $end\n"
		   << "$var wire 1 p pulse $end\n"
		   << "$upscope $end\n"
		   << "$enddefinitions $end\n"
		   << "$dumpvars 0i 0p $end\n";

		FluxmapReader fmr(fluxmap);
		unsigned timestamp = 0;
		unsigned lasttimestamp = 0;
		while (!fmr.eof())
		{
			unsigned ticks;
			uint8_t bits = fmr.getNextEvent(ticks);
			if (fmr.eof())
				break;

			unsigned newtimestamp = timestamp + ticks;
			if (newtimestamp != lasttimestamp)
			{
				of << fmt::format("\n#{} 0i 0p\n", (uint64_t)((lasttimestamp+1) * NS_PER_TICK));
				timestamp = newtimestamp;
				of << fmt::format("#{} ", (uint64_t)(timestamp * NS_PER_TICK));
			}

			if (bits & F_BIT_PULSE)
				of << "1p ";
			if (bits & F_BIT_INDEX)
				of << "1i ";

			lasttimestamp = timestamp;
		}
		of << "\n";
	}

	operator std::string () const
	{
		return fmt::format("vcd({})", _config.directory());
	}

private:
	const VcdFluxSinkProto& _config;
};

std::unique_ptr<FluxSink> FluxSink::createVcdFluxSink(const VcdFluxSinkProto& config)
{
    return std::unique_ptr<FluxSink>(new VcdFluxSink(config));
}

