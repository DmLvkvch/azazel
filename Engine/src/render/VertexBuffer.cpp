#include "VertexBuffer.h"

#include "render/rhi/gl/GLESVertexBuffer.h"

namespace Azazel
{
    VertexBuffer* VertexBuffer::create(const float* vertices, size_t size)
    {
        return new GLESVertexBuffer(vertices, size);
    }
}