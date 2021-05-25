#include "globals.h"
#include "flags.h"
#include "reader.h"
#include "fluxmap.h"
#include "decoders/decoders.h"
#include "macintosh/macintosh.h"
#include "sector.h"
#include "sectorset.h"
#include "record.h"
#include "proto.h"
#include "fluxsource/fluxsource.h"
#include "fluxsink/fluxsink.h"
#include "arch/brother/brother.h"
#include "arch/ibm/ibm.h"
#include "imagewriter/imagewriter.h"
#include "fmt/format.h"
#include "fluxengine.h"
#include <google/protobuf/text_format.h>
#include <fstream>

static FlagGroup flags;

static StringFlag sourceFlux(
	{ "-s", "--source" },
	"flux file to read from",
	"",
	[](const auto& value)
	{
		FluxSource::updateConfigForFilename(config.mutable_input()->mutable_flux(), value);
	});

static StringFlag destImage(
	{ "-o", "--output" },
	"destination image to write",
	"",
	[](const auto& value)
	{
		ImageWriter::updateConfigForFilename(config.mutable_output()->mutable_image(), value);
	});

static StringFlag copyFluxTo(
	{ "--copy-flux-to" },
	"while reading, copy the read flux to this file",
	"",
	[](const auto& value)
	{
		FluxSink::updateConfigForFilename(config.mutable_decoder()->mutable_copy_flux_to(), value);
	});

static StringFlag srcCylinders(
	{ "--cylinders", "-c" },
	"cylinders to read from",
	"",
	[](const auto& value)
	{
		setRange(config.mutable_cylinders(), value);
	});

static StringFlag srcHeads(
	{ "--heads", "-h" },
	"heads to read from",
	"",
	[](const auto& value)
	{
		setRange(config.mutable_heads(), value);
	});

int mainRead(int argc, const char* argv[])
{
	if (argc == 1)
		showProfiles("read", readables);
    flags.parseFlagsWithConfigFiles(argc, argv, readables);

	if (!config.input().has_flux() || !config.output().has_image())
		Error() << "incomplete config (did you remember to specify the format?)";

	if (config.decoder().copy_flux_to().has_drive())
		Error() << "you cannot copy flux to a hardware device";

	std::unique_ptr<FluxSource> fluxSource(FluxSource::create(config.input().flux()));
	std::unique_ptr<AbstractDecoder> decoder(AbstractDecoder::create(config.decoder()));
	std::unique_ptr<ImageWriter> writer(ImageWriter::create(config.output().image()));

	readDiskCommand(*fluxSource, *decoder, *writer);

    return 0;
}

