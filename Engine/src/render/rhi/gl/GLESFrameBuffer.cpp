#include "GLESFrameBuffer.h"
#include "gl_headers.h"

#include <iostream>

namespace Azazel
{
    GLESFrameBuffer::GLESFrameBuffer(Texture* texture)
    {
        glGenFramebuffers(1, &rendererID);
        addColorAttachment(texture);
        depthTarget = nullptr;
    }

    GLESFrameBuffer::GLESFrameBuffer(Texture* texture, FrameBufferTarget* depthTarget)
    {
        glGenFramebuffers(1, &rendererID);
        addColorAttachment(texture);
        setDepthTarget(depthTarget);
    }

    GLESFrameBuffer::GLESFrameBuffer(Texture* texture, Texture* depthTarget)
    {
        glGenFramebuffers(1, &rendererID);
        addColorAttachment(texture);
        setDepthTarget(depthTarget);
    }


    GLESFrameBuffer::~GLESFrameBuffer()
    {
        glDeleteFramebuffers(1, &rendererID);  
    }

    void GLESFrameBuffer::bind() const
    {
        glBindFramebuffer(GL_FRAMEBUFFER, rendererID);
    }
    
    void GLESFrameBuffer::unbind() const
    {
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }

    void GLESFrameBuffer::addColorAttachment(Texture* texture, int slot)
    {
        unsigned int textureId = texture->getRendererId();
        colorTextureTarget[slot] = texture;
        bind();
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + slot, GL_TEXTURE_2D, textureId, 0);
        if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        {
            std::cout << "ERROR::FRAMEBUFFER. Framebuffer is not complete attachment!" << std::endl;
        }
        unbind();
    }

    void GLESFrameBuffer::setDepthTarget(FrameBufferTarget* depthTarget)
    {
        bind();
        // TODO
        unbind();
    }

    void GLESFrameBuffer::setDepthTarget(Texture* depthTexture)
    {
        bind();
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthTexture->getRendererId(), 0);
        unbind();
    }
}