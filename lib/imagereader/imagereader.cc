#include "globals.h"
#include "flags.h"
#include "sector.h"
#include "sectorset.h"
#include "imagereader/imagereader.h"
#include "utils.h"
#include "fmt/format.h"
#include "proto.h"
#include "lib/config.pb.h"
#include <algorithm>
#include <ctype.h>

std::unique_ptr<ImageReader> ImageReader::create(const ImageReaderProto& config)
{
	switch (config.format_case())
	{
		case ImageReaderProto::kImd:
			return ImageReader::createIMDImageReader(config);

		case ImageReaderProto::kImg:
			return ImageReader::createImgImageReader(config);

		case ImageReaderProto::kDiskcopy:
			return ImageReader::createDiskCopyImageReader(config);

		case ImageReaderProto::kJv3:
			return ImageReader::createJv3ImageReader(config);

		case ImageReaderProto::kD64:
			return ImageReader::createD64ImageReader(config);

		default:
			Error() << "bad input file config";
			return std::unique_ptr<ImageReader>();
	}
}

void ImageReader::updateConfigForFilename(ImageReaderProto* proto, const std::string& filename)
{
	static const std::map<std::string, std::function<void(void)>> formats =
	{
		{".adf",      [&]() { proto->mutable_img(); }},
		{".jv3",      [&]() { proto->mutable_jv3(); }},
		{".d64",      [&]() { proto->mutable_d64(); }},
		{".d81",      [&]() { proto->mutable_img(); }},
		{".diskcopy", [&]() { proto->mutable_diskcopy(); }},
		{".img",      [&]() { proto->mutable_img(); }},
		{".imd",      [&]() { proto->mutable_imd(); }},
		{".st",       [&]() { proto->mutable_img(); }},
	};

	std::string FilenameLower;
	FilenameLower = filename;
	for (auto & c: FilenameLower) c = tolower(c); //compare case insensitive if an image on disk is written as .Img it is also oke.

	for (const auto& it : formats)
	{
		if (endsWith(FilenameLower, it.first))
		{
			it.second();
			proto->set_filename(filename);
			return;
		}
	}

	Error() << fmt::format("unrecognised image filename '{}'", filename);
}

ImageReader::ImageReader(const ImageReaderProto& config):
    _config(config)
{}

