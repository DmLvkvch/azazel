#include "Texture.h"

namespace Azazel
{
    Texture::Texture(int width, int height, const unsigned char* data, ColorFormat colorFormat)
    {
    
    }

	Texture::Texture(int width, int height, TextureData textureData)
    {

    }
    Texture::~Texture()
    {
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

    static Texture* createTexture()
    {
        return nullptr;
    }
}