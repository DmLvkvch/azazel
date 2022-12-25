#include "ColorFormat.h"

namespace Azazel
{
    ColorFormat::ColorFormat()
    {

    }

    ColorFormat::~ColorFormat()
    {

    }

    bool ColorFormat::hasAlpha()
    {
        return true;
    }
    
    bool ColorFormat::isDepthFormat()
    {
        return false;
    }
    
    bool ColorFormat::isDepthStencil()
    {
        return false;
    }
    
    int ColorFormat::convertTo(const ColorFormat& format, int value)
    {
        return 0;
    }
    
    int ColorFormat::read(unsigned char* data, int offset)
    {
        return 0;
    }

    void ColorFormat::write(unsigned char* data, int index, int color)
    {
        
    }
}