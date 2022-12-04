#pragma once

#include "ColorFormat.h"

namespace Azazel
{
    class TextureData
    {
    public:
        TextureData(int width, int height, const ColorFormat& colorFormat, int color);
        ~TextureData();
    private:
        void fillData(unsigned char* data, int width, int height, ColorFormat colorFormat, int color);

        unsigned char* data;
        int width;
        int height;
        ColorFormat colorFormat;
    };
}