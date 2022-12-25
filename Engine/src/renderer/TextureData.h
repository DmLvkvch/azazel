#pragma once

#include "ColorFormat.h"

namespace Azazel
{
    class TextureData
    {
    public:
        TextureData() = default;
        TextureData(int width, int height, const ColorFormat& colorFormat, int color);
        TextureData(int width, int height, int bpp, unsigned char* data);
        ~TextureData();

        unsigned char* data;
        int width;
        int height;
        int bpp;
        ColorFormat colorFormat;
    };
}