#include "Texture.h"

#include <renderer/rhi/gl/GLESTexture.h>

namespace Azazel
{
    Texture::Texture(int width, int height, const unsigned char* data)
    {
        textureRHI = new GLESTexture(data, width, height, 4);
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