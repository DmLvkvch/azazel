#include "GLESFrameBuffer.h"
#include "gl_headers.h"

#include <iostream>

namespace Azazel
{

    void FrameBufferStack::activate(unsigned int id)
    {
        this->frameBufferStack.push_back(id);
        glBindFramebuffer(GL_FRAMEBUFFER, id);
    }

    void FrameBufferStack::deactivateLast()
    {
        this->frameBufferStack.pop_back();
        glBindFramebuffer(GL_FRAMEBUFFER, frameBufferStack.back());
    }

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
        frameBufferStack().activate(rendererID);
        addColorAttachment(texture);
        setDepthTarget(depthTarget);
        
        checkFrameBufferStatus();

        frameBufferStack().deactivateLast();
    }

    GLESFrameBuffer::GLESFrameBuffer(Texture* texture, Texture* depthTarget)
    {
        glGenFramebuffers(1, &rendererID);
        frameBufferStack().activate(rendererID);

        addColorAttachment(texture);
        setDepthTarget(depthTarget);

        checkFrameBufferStatus();

        frameBufferStack().deactivateLast();
    }


    GLESFrameBuffer::~GLESFrameBuffer()
    {
        glDeleteFramebuffers(1, &rendererID);  
    }

    void GLESFrameBuffer::bind() const
    {
        frameBufferStack().activate(rendererID);
    }
    
    void GLESFrameBuffer::unbind() const
    {
        frameBufferStack().deactivateLast();
    }

    void GLESFrameBuffer::addColorAttachment(Texture* texture, int slot)
    {
        if (!texture)
        {
            return;
        }
        frameBufferStack().activate(rendererID);
        unsigned int textureId = texture->getRendererID();
        colorTextureTarget[slot] = texture;
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + slot, GL_TEXTURE_2D, textureId, 0);
        frameBufferStack().deactivateLast();
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
        frameBufferStack().activate(rendererID);
        if (depthTarget->checkTargetType<FrameBufferTextureTarget>())
        {
            glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthTarget->getRendererID(), 0);
        }
        else
        {
            glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, depthTarget->getRendererID()); 
        }
        frameBufferStack().deactivateLast();
    }

    void GLESFrameBuffer::setDepthTarget(RenderBuffer* renderBuffer)
    {
        if (!renderBuffer)
        {
            return;
        }
        frameBufferStack().activate(rendererID);
        glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, renderBuffer->getRendererID()); 
        frameBufferStack().deactivateLast();
    }

    void GLESFrameBuffer::setDepthTarget(Texture* depthTexture)
    {
        if (!depthTexture)
        {
            return;
        }
        frameBufferStack().activate(rendererID);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthTexture->getRendererID(), 0);
        frameBufferStack().deactivateLast();
    }
}