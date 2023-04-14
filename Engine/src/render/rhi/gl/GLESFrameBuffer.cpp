#include "GLESFrameBuffer.h"
#include "gl_headers.h"

#include <iostream>

namespace Azazel
{
    GLESFrameBuffer::GLESFrameBuffer(Texture* texture)
    : GLESFrameBuffer(texture, static_cast<Texture*>(nullptr))
    {
        glGenFramebuffers(1, &rendererID);
        addColorAttachment(texture);
        depthTarget = nullptr;
    }

    GLESFrameBuffer::GLESFrameBuffer(Texture* texture, FrameBufferTarget* depthTarget)
    {
        glGenFramebuffers(1, &rendererID);
        bind();
        addColorAttachment(texture);
        setDepthTarget(depthTarget);
        
        checkFrameBufferStatus();

        unbind();
    }

    GLESFrameBuffer::GLESFrameBuffer(Texture* texture, Texture* depthTarget)
    {
        glGenFramebuffers(1, &rendererID);
        bind();

        addColorAttachment(texture);
        setDepthTarget(depthTarget);

        checkFrameBufferStatus();

        unbind();
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
        if (!texture)
        {
            return;
        }

        unsigned int textureId = texture->getRendererID();
        colorTextureTarget[slot] = texture;
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + slot, GL_TEXTURE_2D, textureId, 0);
    }

    int GLESFrameBuffer::checkFrameBufferStatus()
    {
        if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        {
            std::cout << "ERROR::FRAMEBUFFER. Framebuffer is not complete attachment!" << std::endl;
            //throw std::exception("FrameBuffer incomplete attachment." + glGetError());
        }
        return GL_FRAMEBUFFER_COMPLETE;
    }

    void GLESFrameBuffer::setDepthTarget(FrameBufferTarget* depthTarget)
    {
        if (!depthTarget)
        {
            return;
        }
        bind();
        if (depthTarget->checkTargetType<FrameBufferTextureTarget>())
        {
            glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthTarget->getRendererID(), 0);
        }
        else
        {
            glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, depthTarget->getRendererID()); 
        }
        unbind();
    }

    void setDepthTarget(RenderBuffer* renderBuffer)
    {
        if (!renderBuffer)
        {
            return;
        }
        glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, renderBuffer->getRendererID()); 
    }

    void GLESFrameBuffer::setDepthTarget(Texture* depthTexture)
    {
        if (!depthTexture)
        {
            return;
        }
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthTexture->getRendererID(), 0);
    }
}