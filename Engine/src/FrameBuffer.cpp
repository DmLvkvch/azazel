#include "FrameBuffer.h"
#include "Texture.h"
#include "gl_headers.h"

#include <iostream>
namespace Azazel
{
	FrameBuffer::FrameBuffer()
    {
        glGenFramebuffers(1, &rendererId);

        this->texture = new Texture(0xffff0000);
        setTextureTarget(this->texture);
    }

	FrameBuffer::~FrameBuffer()
    {
        glDeleteFramebuffers(1, &rendererId);  
    }

	void FrameBuffer::bind()
    {
        glBindFramebuffer(GL_FRAMEBUFFER, rendererId);
    }
	
    void FrameBuffer::unbind()
    {
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }

    void FrameBuffer::setTextureTarget(Texture* texture)
    {
        int textureId = texture->getRendererId();
        texture->bind();
        bind();
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, textureId, 0);
        if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        {
	        std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;
        }
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        unbind();
        texture->unbind();
    }

    void FrameBuffer::setFrameBufferDepthTarget(FrameBufferTarget* frameBufferTarget)
    {

    }
}