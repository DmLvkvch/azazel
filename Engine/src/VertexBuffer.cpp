#include "VertexBuffer.h"

#include "gl_headers.h"

VertexBuffer::VertexBuffer(const void* data, int size)
{
	glGenBuffers(1, &rendererId);
    glBindBuffer(GL_ARRAY_BUFFER, rendererId);
    glBufferData(GL_ARRAY_BUFFER, size, data, GL_DYNAMIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

VertexBuffer::~VertexBuffer()
{
    glDeleteBuffers(1, &rendererId);
}

void VertexBuffer::bind()
{
    glBindBuffer(GL_ARRAY_BUFFER, rendererId);
}

void VertexBuffer::unbind()
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}
