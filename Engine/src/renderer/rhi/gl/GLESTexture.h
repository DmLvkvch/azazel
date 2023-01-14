#pragma once

#include <string>
#include <renderer/Texture.h>

namespace Azazel
{
    class GLESTexture : public Texture
    {
    private:
        unsigned int rendererId;
        unsigned int textureFilterToGLFormat(Texture::TextureFilter textureFilter);
        unsigned int textureWrapToGLFormat(Texture::TextureWrap textureWrap);
        void createTexture(int width, int height, int bpp, const unsigned char* data);
    public:
        GLESTexture (const TextureData& textureData);
        GLESTexture(int width, int height, int color);
        GLESTexture(int width, int height, int bpp, const unsigned char* data);
        ~GLESTexture();
        void bind(unsigned int slot = 0) const override;
        void unbind() const override;
        void setTextureFilter(Texture::TextureFilter textureFilter) override;
        void setTextureWrap(Texture::TextureWrap textureWrap) override;
        unsigned int getRendererId() const override;
    };
}