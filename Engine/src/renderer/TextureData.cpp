#include "TextureData.h"

namespace Azazel
{
    TextureData::TextureData(int width, int height, const ColorFormat& colorFormat, int color)
    : width(width), height(height), colorFormat(colorFormat)
    {
        
    }

    TextureData::TextureData(int width, int height, int bpp, unsigned char* data)
    : width(width), height(height), bpp(bpp), data(data)
    {

    }

    TextureData::~TextureData()
    {

    }

    void TextureData::fillData(unsigned char* data, int width, int height, ColorFormat colorFormat, int color)
    {

    }
}