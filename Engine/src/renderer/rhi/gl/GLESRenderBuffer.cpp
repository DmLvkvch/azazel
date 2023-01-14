#include "GLESRenderBuffer.h"

#include "gl_headers.h"

namespace Azazel
{
    GLESRenderBuffer::GLESRenderBuffer(int width, int height)
    :RenderBuffer(width, height)
    {
        glGenRenderbuffers(1, &rendererId);
        bind();
        glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24, width, height);
        unbind();
    }

    GLESRenderBuffer::~GLESRenderBuffer()
    {
        glDeleteRenderbuffers(1, &rendererId);
    }

    int GLESRenderBuffer::getRendererId() const
    {
        return rendererId;
    }
    
    void GLESRenderBuffer::bind() const
    {
        glBindRenderbuffer(GL_RENDERBUFFER, rendererId);
    }

    void GLESRenderBuffer::unbind() const
    {
        glBindRenderbuffer(GL_RENDERBUFFER, 0);
    }
}
