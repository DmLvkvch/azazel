#include "GLESVertexArray.h"

#include "gl_headers.h"
#include <vector>
#include <iostream>

namespace Azazel
{
    GLESVertexArray::GLESVertexArray()
    {
        glGenVertexArrays(1, &rendererID);
    }

    GLESVertexArray::~GLESVertexArray()
    {
        glDeleteVertexArrays(1, &rendererID);
    }

    void GLESVertexArray::addBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer, const BufferLayout& layout)
    {
        bind();
        vertexBuffer->bind();
        const std::vector<BufferElement>& elements = layout.getElements();
        unsigned int offset = 0;
        for (unsigned int i = 0; i < elements.size(); i++)
        {
            const BufferElement& element = elements[i];
            offset = element.offset;
            glEnableVertexAttribArray(i);
            glVertexAttribPointer(i, element.getComponentCount(), shaderTypeToGLType(element.type), 
                                    element.normalized ? GL_TRUE : GL_FALSE,
                                    layout.getStride(), reinterpret_cast<const void *>(offset));
        }
        vertexBuffer->unbind();
        unbind();
        vertexBuffers.push_back(vertexBuffer);
        size += vertexBuffer->getBufferLayout().getSize();
    }

    void GLESVertexArray::bind() const
    {
        glBindVertexArray(rendererID);
    }

    void GLESVertexArray::unbind() const
    {
        glBindVertexArray(0);
    }
}