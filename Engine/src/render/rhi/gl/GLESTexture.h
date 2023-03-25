#pragma once

#include <string>
#include "render/Texture.h"

namespace Azazel
{
    class GLESTexture : public Texture
    {
    public:
        GLESTexture (const TextureData& textureData);
        GLESTexture(int width, int height, int color);
        GLESTexture(int width, int height, int bpp, const unsigned char* data);
        ~GLESTexture();
        void bind(unsigned int slot = 0) const override;
        void unbind() const override;
        void setTextureFilter(Texture::TextureFilter textureFilter) override;
        void setTextureWrap(Texture::TextureWrap textureWrap) override;
        const unsigned int getRendererId() const override;
    private:
        unsigned int textureFilterToGLFormat(Texture::TextureFilter textureFilter);
        unsigned int textureWrapToGLFormat(Texture::TextureWrap textureWrap);
        void createTexture(int width, int height, int bpp, const unsigned char* data);
    private:
        unsigned int rendererID;
    };
}