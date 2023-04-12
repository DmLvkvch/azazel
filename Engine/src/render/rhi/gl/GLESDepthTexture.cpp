#include "GLESDepthTexture.h"

namespace Azazel
{
    GLESDepthTexture::GLESDepthTexture(const TextureData& textureData)
    {
        glGenTextures(1, &rendererID);
        bind();
        glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT24, textureData.width, textureData.height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, nullptr);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE, GL_COMPARE_REF_TO_TEXTURE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_FUNC, GL_LEQUAL);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        
        this->width = textureData.width;
        this->height = textureData.height;
        this->data = nullptr;
        this->bpp = 3;
        unbind();
    }

    GLESDepthTexture::~GLESDepthTexture()
    {
        glDeleteTextures(1, &rendererID);
    }

    void GLESDepthTexture::bind(unsigned int slot) const
    {
        glActiveTexture(GL_TEXTURE0 + slot);
        glBindTexture(GL_TEXTURE_2D, rendererID);
    }

    void GLESDepthTexture::unbind() const
    {
        glBindTexture(GL_TEXTURE_2D, 0);
    }
}