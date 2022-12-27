#include "GLESVertexBuffer.h"

#include "gl_headers.h"

namespace Azazel
{
    GLESVertexBuffer::GLESVertexBuffer(const void* data, int size)
    {
        glGenBuffers(1, &rendererId);
        glBindBuffer(GL_ARRAY_BUFFER, rendererId);
        glBufferData(GL_ARRAY_BUFFER, size, data, GL_DYNAMIC_DRAW);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    GLESVertexBuffer::~GLESVertexBuffer()
    {
        glDeleteBuffers(1, &rendererId);
    }

    void GLESVertexBuffer::bind() const
    {
        glBindBuffer(GL_ARRAY_BUFFER, rendererId);
    }

    void GLESVertexBuffer::unbind() const
    {
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    void GLESVertexBuffer::setLayout(const BufferLayout& bufferLayout)
    {
         this->bufferLayout = bufferLayout;
    }

    const BufferLayout& GLESVertexBuffer::getBufferlayout() const
    {
        return bufferLayout;
    }
}