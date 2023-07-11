#include "GLESFrameBuffer.h"
#include "gl_headers.h"

#include <iostream>
#include "GLESFrameBufferHistory.h"

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
        frameBufferHistory().activate(rendererID);
        addColorAttachment(texture);
        setDepthTarget(depthTarget);
        
        checkFrameBufferStatus();

        frameBufferHistory().deactivateLast();
    }

    GLESFrameBuffer::GLESFrameBuffer(Texture* texture, Texture* depthTarget)
    {
        glGenFramebuffers(1, &rendererID);
        frameBufferHistory().activate(rendererID);

        addColorAttachment(texture);
        setDepthTarget(depthTarget);

        checkFrameBufferStatus();

        frameBufferHistory().deactivateLast();
    }


    GLESFrameBuffer::~GLESFrameBuffer()
    {
        glDeleteFramebuffers(1, &rendererID);  
    }

    void GLESFrameBuffer::bind() const
    {
        frameBufferHistory().activate(rendererID);
    }
    
    void GLESFrameBuffer::unbind() const
    {
        frameBufferHistory().deactivateLast();
    }

    void GLESFrameBuffer::addColorAttachment(Texture* texture, int slot)
    {
        if (!texture)
        {
            return;
        }
        frameBufferHistory().activate(rendererID);
        unsigned int textureId = texture->getRendererID();
        colorTextureTarget[slot] = texture;
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + slot, GL_TEXTURE_2D, textureId, 0);
        frameBufferHistory().deactivateLast();
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
        frameBufferHistory().activate(rendererID);
        if (depthTarget->checkTargetType<FrameBufferTextureTarget>())
        {
            glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthTarget->getRendererID(), 0);
        }
        else
        {
            glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, depthTarget->getRendererID()); 
        }
        frameBufferHistory().deactivateLast();
    }

    void GLESFrameBuffer::setDepthTarget(RenderBuffer* renderBuffer)
    {
        if (!renderBuffer)
        {
            return;
        }
        frameBufferHistory().activate(rendererID);
        glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, renderBuffer->getRendererID()); 
        frameBufferHistory().deactivateLast();
    }

    void GLESFrameBuffer::setDepthTarget(Texture* depthTexture)
    {
        if (!depthTexture)
        {
            return;
        }
        frameBufferHistory().activate(rendererID);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthTexture->getRendererID(), 0);
        frameBufferHistory().deactivateLast();
    }
}