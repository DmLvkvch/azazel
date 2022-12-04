#include "GLESFrameBuffer.h"
#include "GLESTexture.h"
#include "gl_headers.h"

#include <iostream>
namespace Azazel
{
	GLESFrameBuffer::GLESFrameBuffer(TextureRHI* texture) : frameBufferDepthTarget(nullptr)
    {
        glGenFramebuffers(1, &rendererId);
        this->colorAttachments.push_back(texture);
        setTextureTarget(texture);
    }

    GLESFrameBuffer::GLESFrameBuffer(const std::vector<TextureRHI*>& colorAttachments) : frameBufferDepthTarget(nullptr)
    {
        glGenFramebuffers(1, &rendererId);
        this->colorAttachments.insert(this->colorAttachments.end(), colorAttachments.begin(), colorAttachments.end());
        for (int i = 0; i < colorAttachments.size(); i++)
        {
            setTextureTarget(colorAttachments[i], i);
        }
    }

    GLESFrameBuffer::~GLESFrameBuffer()
    {
        glDeleteFramebuffers(1, &rendererId);  
    }

	void GLESFrameBuffer::bind()
    {
        glBindFramebuffer(GL_FRAMEBUFFER, rendererId);
    }
	
    void GLESFrameBuffer::unbind()
    {
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }

    void GLESFrameBuffer::setTextureTarget(TextureRHI* texture, int slot)
    {
        unsigned int textureId = texture->getRendererId();
        bind();
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + slot, GL_TEXTURE_2D, textureId, 0);
        if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        {
	        std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete attachment!" << std::endl;
        }
        unbind();
    }

    void GLESFrameBuffer::setFrameBufferDepthTarget(FrameBufferTarget* frameBufferTarget)
    {

    }
}