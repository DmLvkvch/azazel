#pragma once

#include "render/Texture.h"

#include "gl_headers.h"

namespace Azazel
{
    class GLESDepthTexture : public Texture
    {
    public:
        GLESDepthTexture(const TextureData& textureData)
        {
            glGenTextures(1, &rendererID);
            glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT24, textureData.width, textureData.height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, nullptr);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); 
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);  
        }

        ~GLESDepthTexture()
        {
            glDeleteTextures(1, &rendererID);
        }

        void bind(unsigned int slot = 0) const override
        {
            glBindTexture(GL_TEXTURE_2D, rendererID);
        }

        void unbind() const override
        {
            glBindTexture(GL_TEXTURE_2D, 0);
        }

        void setTextureFilter(Texture::TextureFilter textureFilter) override
        {

        }

        void setTextureWrap(Texture::TextureWrap textureWrap) override
        {

        }

        const unsigned int getRendererId() const override
        {
            return rendererID;
        }

    private:
        unsigned int rendererID;
    };
}