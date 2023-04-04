#include "GLESVertexBuffer.h"

#include "gl_headers.h"

namespace Azazel
{
    GLESVertexBuffer::GLESVertexBuffer(const void* data, size_t size)
    {
        glGenBuffers(1, &rendererID);
        glBindBuffer(GL_ARRAY_BUFFER, rendererID);
        glBufferData(GL_ARRAY_BUFFER, size, data, GL_DYNAMIC_DRAW);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    GLESVertexBuffer::~GLESVertexBuffer()
    {
        glDeleteBuffers(1, &rendererID);
    }

    void GLESVertexBuffer::bind() const
    {
        glBindBuffer(GL_ARRAY_BUFFER, rendererID);
    }

    void GLESVertexBuffer::unbind() const
    {
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    void GLESVertexBuffer::updateSubData(int offset, void* data, int size)
    {
        glBufferSubData(GL_ARRAY_BUFFER, offset, size, data);
    }

    void GLESVertexBuffer::updateData(void* data, int size)
    {
        glBufferData(GL_ARRAY_BUFFER, size, data, GL_DYNAMIC_DRAW);
    }

    void GLESVertexBuffer::setLayout(const BufferLayout& bufferLayout)
    {
         this->bufferLayout = bufferLayout;
    }

    const BufferLayout& GLESVertexBuffer::getBufferLayout() const
    {
        return bufferLayout;
    }
}