#include "GLESRenderBuffer.h"

#include "gl_headers.h"

namespace Azazel
{
    GLESRenderBuffer::GLESRenderBuffer(int width, int height)
    {
        glGenRenderbuffers(1, &rendererId);
        bind();
        glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
        unbind();
    }

    GLESRenderBuffer::~GLESRenderBuffer()
    {
        glDeleteRenderbuffers(1, &rendererId);
    }
    
    void GLESRenderBuffer::bind()
    {
        glBindRenderbuffer(GL_RENDERBUFFER, rendererId);
    }

    void GLESRenderBuffer::unbind()
    {
        glBindRenderbuffer(GL_RENDERBUFFER, 0);
    }
}
