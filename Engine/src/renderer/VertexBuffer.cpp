#include "VertexBuffer.h"

#include "rhi/gl/GLESVertexBuffer.h"

namespace Azazel
{
    VertexBuffer* VertexBuffer::create(float* vertices, size_t size)
    {
        return new GLESVertexBuffer(vertices, size);
    }
}