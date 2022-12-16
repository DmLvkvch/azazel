#pragma once

#include <string>

namespace Azazel
{
    class ColorFormat
    {
    public:
        ColorFormat();
        virtual ~ColorFormat();
        bool hasAlpha();
        bool isDepthFormat();
        bool isDepthStencil();
        int convertTo(const ColorFormat& format, int value);
        int read(unsigned char* data, int offset);
        void write(unsigned char* data, int index, int color);

    private:
        std::string name;
        int bpp;
    };
}