#include "GLESDepthTexture.h"

namespace Azazel
{
    GLESDepthTexture::GLESDepthTexture(const TextureData& textureData)
    {
        glGenTextures(1, &rendererID);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT24, textureData.width, textureData.height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, nullptr);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    }

    GLESDepthTexture::~GLESDepthTexture()
    {
        glDeleteTextures(1, &rendererID);
    }

    void GLESDepthTexture::bind(unsigned int slot) const
    {
        glBindTexture(GL_TEXTURE_2D, rendererID);
    }

    void GLESDepthTexture::unbind() const
    {
        glBindTexture(GL_TEXTURE_2D, 0);
    }
}