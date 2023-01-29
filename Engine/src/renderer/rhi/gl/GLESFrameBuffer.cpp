#include "GLESFrameBuffer.h"
#include "gl_headers.h"

#include <iostream>
namespace Azazel
{
    GLESFrameBuffer::GLESFrameBuffer(std::shared_ptr<Texture> texture)
    {
        glGenFramebuffers(1, &rendererId);
        addColorAttachment(texture);
        depthTarget = std::shared_ptr<FrameBufferTarget>(nullptr);
    }

    GLESFrameBuffer::GLESFrameBuffer(std::shared_ptr<Texture> texture, std::shared_ptr<FrameBufferTarget> depthTarget)
    {
        glGenFramebuffers(1, &rendererId);
        addColorAttachment(texture);
        setDepthTarget(depthTarget);
    }

    GLESFrameBuffer::~GLESFrameBuffer()
    {
        glDeleteFramebuffers(1, &rendererId);  
    }

    void GLESFrameBuffer::bind() const
    {
        glBindFramebuffer(GL_FRAMEBUFFER, rendererId);
    }
    
    void GLESFrameBuffer::unbind() const
    {
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }

    void GLESFrameBuffer::addColorAttachment(std::shared_ptr<Texture> texture, int slot)
    {
        unsigned int textureId = texture->getRendererId();
        colorTextureTarget = texture;
        bind();
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + slot, GL_TEXTURE_2D, textureId, 0);
        if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        {
            std::cout << "ERROR::FRAMEBUFFER. Framebuffer is not complete attachment!" << std::endl;
        }
        unbind();
    }

    void GLESFrameBuffer::setDepthTarget(std::shared_ptr<FrameBufferTarget> depthTarget)
    {
        bind();
        // TODO
        unbind();
    }

}