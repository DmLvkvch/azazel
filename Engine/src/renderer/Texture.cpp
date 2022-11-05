#include "Texture.h"

namespace Azazel
{
    Texture::Texture(int width, int height, const char* data)
    {

    }

    Texture::~Texture()
    {
        if (data != nullptr)
        {
            delete[] data;
        }
        delete textureRHI;
    }

    int Texture::getWidth()
    {
        return width;
    }

    int Texture::getHeight()
    {
        return height;
    }

    ColorFormat Texture::getColorFormat()
    {
        return colorFormat;
    }

    TextureRHI* Texture::getTextureRHI()
    {
        return textureRHI;
    }
}