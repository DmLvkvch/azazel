#include "AZTexture.h"

namespace Azazel
{
    VKTexture::VKTexture(const TextureData& textureData)
    : Texture(textureData.width, textureData.height, textureData.bpp, textureData.data, Format::RGBA32)
    {
        createTexture(getWidth(), getHeight(), getBpp(), textureData.data);
    }

    VKTexture::VKTexture(int width, int height, int bpp, const unsigned char* data)
    : Texture(width, height, bpp, data, Format::RGBA32)
    {
        createTexture(width, height, bpp, data);
    }

    VKTexture::VKTexture(int width, int height, int color)
    {
        unsigned char* data = new unsigned char[width * height * 4];
        unsigned char b = (color >> 0 ) & 0xff;
        unsigned char g = (color >> 8 ) & 0xff;
        unsigned char r = (color >> 16) & 0xff;
        unsigned char a = (color >> 24) & 0xff;
        for (int i = 0; i < width * height * 4; i += 4)
        {
            data[i + 0] = r;
            data[i + 1] = g;
            data[i + 2] = b;
            data[i + 3] = a;
        }
        createTexture(width, height, 4, data);
    }

    void VKTexture::createTexture(int width, int height, int bpp, const unsigned char* data)
    {
        
    }

    VKTexture::~VKTexture()
    {
    }

    void VKTexture::bind(unsigned int slot) const
    {
    }

    void VKTexture::unbind() const
    {
    }

    unsigned int VKTexture::textureFilterToGLFormat (Texture::TextureFilter textureFilter)
    {

        return 0;
    }

    unsigned int VKTexture::textureWrapToGLFormat (Texture::TextureWrap textureWrap)
    {
       
        return 0;
    }

    void VKTexture::setTextureFilter(Texture::TextureFilter textureFilter)
    {
    }

    void VKTexture::setTextureWrap(Texture::TextureWrap textureWrap)
    {
    }

    const unsigned int VKTexture::getRendererID() const
    {
        return rendererID;
    }
}