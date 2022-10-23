#include "VertexArray.h"

#include "gl_headers.h"

VertexArray::VertexArray()
{
	glGenVertexArrays(1, &rendererId);
}

VertexArray::~VertexArray()
{
	glDeleteVertexArrays(1, &rendererId);
}

void VertexArray::addBuffer(VertexBuffer& vertexBuffer, const VertexBufferLayout& layout)
{
    bind();
    vertexBuffer.bind();
    const std::vector<VertexBufferElement> elements = layout.getElements();
    unsigned int offset = 0;
    for (unsigned int i = 0; i < elements.size(); i++)
    {
        const VertexBufferElement& element = elements[i];
        glEnableVertexAttribArray(i);
        glVertexAttribPointer(i, element.count, element.type, element.normalized,
                                layout.getStride(), reinterpret_cast<const void *>(offset));
        offset += element.count * VertexBufferElement::getSizeOfType(element.type);
    }
    vertexBuffer.unbind();
    unbind();
}

void VertexArray::bind()
{
    glBindVertexArray(rendererId);
}

void VertexArray::unbind()
{
    glBindVertexArray(0);
}
