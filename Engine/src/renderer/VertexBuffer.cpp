#include "VertexBuffer.h"

#include "rhi/gl/GLESVertexBuffer.h"

namespace Azazel
{
    VertexBuffer* VertexBuffer::create(float* vertices, int size)
    {
        return new GLESVertexBuffer(vertices, size);
    }
}