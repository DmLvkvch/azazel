#include "FrameBuffer.h"
#include "Texture.h"
#include "gl_headers.h"

namespace Azazel
{
	FrameBuffer::FrameBuffer()
    {
        glGenFramebuffers(1, &rendererId);

        this->texture = new Texture(0xffff0000);
        int textureId = texture->getRendererId();
        bind();
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, textureId, 0);
        unbind();
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
}