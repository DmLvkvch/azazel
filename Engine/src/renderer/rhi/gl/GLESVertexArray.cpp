#include "GLESVertexArray.h"

#include "gl_headers.h"
#include <vector>
#include "renderer/rhi/gl/GLESVertexBufferLayout.h"

namespace Azazel
{
    GLESVertexArray::GLESVertexArray()
    : lastIndex(0)
    {
        glGenVertexArrays(1, &rendererId);
    }

    GLESVertexArray::~GLESVertexArray()
    {
        glDeleteVertexArrays(1, &rendererId);
    }

    void GLESVertexArray::addBuffer(VertexBuffer& vertexBuffer, const GLESVertexBufferLayout& layout)
    {
        bind();
        vertexBuffer.bind();
        const std::vector<GLESVertexBufferElement>& elements = layout.getElements();
        unsigned int offset = 0;
        for (unsigned int i = 0; i < elements.size(); i++)
        {
            const GLESVertexBufferElement& element = elements[i];
            glEnableVertexAttribArray(lastIndex);
            glVertexAttribPointer(lastIndex, element.count, element.type, element.normalized,
                                    layout.getStride(), reinterpret_cast<const void *>(offset));
            lastIndex++;
            offset += element.count * element.getSizeOfType();
        }
        vertexBuffer.unbind();
        unbind();
    }

    void GLESVertexArray::bind() const
    {
        glBindVertexArray(rendererId);
    }

    void GLESVertexArray::unbind() const
    {
        glBindVertexArray(0);
    }
}