#include "TextureData.h"

// #ifdef _DEBUG
// #define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
// #else
// #define DBG_NEW new
// #endif

namespace Azazel
{
    TextureData::TextureData(int width, int height, int color)
    : width(width), height(height)
    {
        unsigned char* data = new unsigned char[width * height * 4];
        unsigned char a = (color >> 0 ) & 0xff;
        unsigned char b = (color >> 8 ) & 0xff;
        unsigned char g = (color >> 16) & 0xff;
        unsigned char r = (color >> 24) & 0xff;
        for (int i = 0; i < width * height * 4; i += 4)
        {
            data[i + 0] = r;
            data[i + 1] = g;
            data[i + 2] = b;
            data[i + 3] = a;
        }
        this->data = data;
        this->bpp = 4;
        this->width = width;
        this->height = height;
    }

    TextureData::TextureData(int width, int height, int bpp, unsigned char* data)
    : width(width), height(height), bpp(bpp), data(data)
    {
    }

    TextureData::~TextureData()
    {
       
    }
}