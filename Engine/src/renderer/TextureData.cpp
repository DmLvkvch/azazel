#include "TextureData.h"

namespace Azazel
{
    TextureData::TextureData(int width, int height, const ColorFormat& colorFormat, int color)
    : width(width), height(height), colorFormat(colorFormat)
    {
        unsigned char* data = new unsigned char[width * height * 4];
        unsigned char b = color & 0xff;
        unsigned char g = (color >> 8) & 0xff;
        unsigned char r = (color >> 16) & 0xff;
        unsigned char a = (color >> 24) & 0xff;
        for (int i = 0; i < width * height * 4; i += 4)
        {
            data[i + 0] = r;
            data[i + 1] = g;
            data[i + 2] = g;
            data[i + 3] = a;
        }
        this->data = data;
        this->bpp = 4;
    }

    TextureData::TextureData(int width, int height, int bpp, unsigned char* data)
    : width(width), height(height), bpp(bpp), data(data)
    {
    }

    TextureData::~TextureData()
    {

    }
}