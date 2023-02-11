#pragma once

namespace Azazel
{
    class TextureData
    {
    public:
        TextureData() = default;
        TextureData(int width, int height, int color);
        TextureData(int width, int height, int bpp, unsigned char* data);
        ~TextureData();

        unsigned char* data;
        int width;
        int height;
        int bpp;
    };
}