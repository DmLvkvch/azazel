#include "GLESIndexBuffer.h"

#include "gl_headers.h"

namespace Azazel
{
    GLESIndexBuffer::GLESIndexBuffer(const void* data, size_t count)
    {
        this->count = count;
        glGenBuffers(1, &rendererId);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, rendererId);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_DYNAMIC_DRAW);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }

    GLESIndexBuffer::~GLESIndexBuffer()
    {
        glDeleteBuffers(1, &rendererId);
    }

    void GLESIndexBuffer::bind() const
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, rendererId);
    }

    void GLESIndexBuffer::unbind() const
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }

    size_t GLESIndexBuffer::getElementCount() const
    {
        return count;
    }
}