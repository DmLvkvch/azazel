#include "RenderBuffer.h"

#include "gl_headers.h"

namespace Azazel
{
    RenderBuffer::RenderBuffer(int width, int height)
    {
        glGenRenderbuffers(1, &rendererId);
        bind();
        glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
        unbind();
    }

    RenderBuffer::~RenderBuffer()
    {
        glDeleteRenderbuffers(1, &rendererId);
    }
    
    void RenderBuffer::bind()
    {
        glBindRenderbuffer(GL_RENDERBUFFER, rendererId);
    }

    void RenderBuffer::unbind()
    {
        glBindRenderbuffer(GL_RENDERBUFFER, 0);
    }
}
