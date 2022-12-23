#include "GLESFrameBuffer.h"
#include "GLESTexture.h"
#include "gl_headers.h"

#include <iostream>
namespace Azazel
{
	GLESFrameBuffer::GLESFrameBuffer(Texture* texture, FrameBufferTarget* frameBufferTarget)
    {
        glGenFramebuffers(1, &rendererId);
        this->colorAttachments.push_back(texture);
        addColorAttachment(texture);
    }

    GLESFrameBuffer::GLESFrameBuffer(const std::vector<Texture*>& colorAttachments) : frameBufferDepthTarget(nullptr)
    {
        glGenFramebuffers(1, &rendererId);
        this->colorAttachments.insert(this->colorAttachments.end(), colorAttachments.begin(), colorAttachments.end());
        for (int i = 0; i < colorAttachments.size(); i++)
        {
            addColorAttachment(colorAttachments[i], i);
        }
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

    void GLESFrameBuffer::addColorAttachment(const Texture* texture, int slot)
    {
        unsigned int textureId = texture->getRendererId();
        bind();
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + slot, GL_TEXTURE_2D, textureId, 0);
        if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        {
	        std::cout << "ERROR::FRAMEBUFFER. Framebuffer is not complete attachment!" << std::endl;
        }
        unbind();
    }

    void GLESFrameBuffer::setDepthTarget(FrameBufferTarget* frameBufferTarget)
    {
        bind();
        // TODO
        unbind();
    }

}