#include "GLESVertexArray.h"

#include "gl_headers.h"
#include <vector>
#include "renderer/rhi/gl/GLESVertexBufferLayout.h"

namespace Azazel
{
    GLESVertexArray::GLESVertexArray()
    {
        glGenVertexArrays(1, &rendererId);
    }

    GLESVertexArray::~GLESVertexArray()
    {
        glDeleteVertexArrays(1, &rendererId);
    }

    void GLESVertexArray::addBuffer(VertexBuffer& vertexBuffer, VertexBufferLayout* layout, int attribOffset)
    {
        bind();
        vertexBuffer.bind();
        const std::vector<VertexBufferElement> elements = layout->getElements();
        unsigned int offset = 0;
        for (unsigned int i = 0; i < elements.size(); i++)
        {
            const VertexBufferElement& element = elements[i];
            glEnableVertexAttribArray(i + attribOffset);
            glVertexAttribPointer(i + attribOffset, element.count, element.type, element.normalized,
                                    layout->getStride(), reinterpret_cast<const void *>(offset));
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