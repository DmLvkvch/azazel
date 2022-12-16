#include "Texture.h"

#include "rhi/gl/GLESTexture.h"

namespace Azazel
{
    Texture::Texture(int width, int height, const unsigned char* data, ColorFormat colorFormat)
    {
    
    }

	Texture::Texture(const TextureData& textureData)
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

    Texture* Texture::create(const TextureData& textureData)
    {
        return new GLESTexture(textureData);
    }
}