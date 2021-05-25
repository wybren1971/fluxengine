#include "globals.h"
#include "flags.h"
#include "fmt/format.h"
#include "dep/agg/include/agg2d.h"
#include "dep/stb/stb_image_write.h"
#include "utils.h"
#include "bitmap.h"
#include <regex>
#include <sstream>

Bitmap::Bitmap(const std::string filename, unsigned width, unsigned height):
    filename(filename),
    width(width),
    height(height),
    initialised(true)
{}

Agg2D& Bitmap::painter()
{
	if (!_painter)
	{
		_bitmap.resize(width * height * 4, 255);
		_painter.reset(new Agg2D());
		_painter->attach(&_bitmap[0], width, height, width*4);
	}
	return *_painter;
}

void Bitmap::save()
{
	if (endsWith(filename, ".png"))
		stbi_write_png(filename.c_str(), width, height, 4, &_bitmap[0], width*4);
	else if (endsWith(filename, ".bmp"))
		stbi_write_bmp(filename.c_str(), width, height, 4, &_bitmap[0]);
	else if (endsWith(filename, ".tga"))
		stbi_write_tga(filename.c_str(), width, height, 4, &_bitmap[0]);
	else if (endsWith(filename, ".jpg"))
		stbi_write_jpg(filename.c_str(), width, height, 4, &_bitmap[0], 80);
	else
		Error() << "don't know how to write that image format";
}

