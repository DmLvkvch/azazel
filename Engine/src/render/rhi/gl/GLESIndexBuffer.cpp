#include "GLESIndexBuffer.h"

#include "gl_headers.h"

namespace Azazel
{
    GLESIndexBuffer::GLESIndexBuffer(const void* data, unsigned int count)
    {
        this->count = count;
        glGenBuffers(1, &rendererID);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, rendererID);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_DYNAMIC_DRAW);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }

    GLESIndexBuffer::~GLESIndexBuffer()
    {
        glDeleteBuffers(1, &rendererID);
    }

    void GLESIndexBuffer::bind() const
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, rendererID);
    }

    void GLESIndexBuffer::unbind() const
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }

    unsigned int GLESIndexBuffer::getElementCount() const
    {
        return count;
    }
}