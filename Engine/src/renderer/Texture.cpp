#include "Texture.h"

#include "rhi/gl/GLESTexture.h"

namespace Azazel
{
    Texture::Texture(int width, int height, int bpp, const unsigned char* data, Format format)
    : width(width), height(height), bpp(bpp), data(data)
    {
    }

    Texture::Texture(const TextureData& textureData)
    {
    }
    
    Texture::~Texture()
    {
    }

    void Texture::setLabel(const std::string& label)
    {
        this->label = label;
    }


    Texture* Texture::create(const TextureData& textureData)
    {
        return new GLESTexture(textureData);
    }

    Texture* Texture::create(int width, int height, int color)
    {
        TextureData textureData (width, height, color);
        return new GLESTexture(textureData);
    }
}