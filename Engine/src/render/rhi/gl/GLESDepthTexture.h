#pragma once

#include "render/Texture.h"
#include "gl_headers.h"

namespace Azazel
{
    class GLESDepthTexture : public Texture
    {
    public:
        GLESDepthTexture(const TextureData& textureData);

        ~GLESDepthTexture();

        void bind(unsigned int slot = 0) const override;

        void unbind() const override;

        void setTextureFilter(Texture::TextureFilter textureFilter) override
        {

        }

        void setTextureWrap(Texture::TextureWrap textureWrap) override
        {

        }

        const unsigned int getRendererID() const override
        {
            return rendererID;
        }

    private:
        unsigned int rendererID;
    };
}