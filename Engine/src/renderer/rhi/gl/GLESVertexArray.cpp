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

    void GLESVertexArray::addBuffer(VertexBuffer& vertexBuffer, const BufferLayout& layout)
    {
        bind();
        vertexBuffer.bind();
        const std::vector<BufferElement>& elements = layout.getElements();
        unsigned int offset = 0;
        for (unsigned int i = 0; i < elements.size(); i++)
        {
            const BufferElement& element = elements[i];
            glEnableVertexAttribArray(i);
            offset = element.offset;
            glVertexAttribPointer(i, element.getComponentCount(), shaderTypeToGLType(element.type), element.normalized ? GL_TRUE : GL_FALSE,
                                    layout.getStride(), reinterpret_cast<const void *>(offset));
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