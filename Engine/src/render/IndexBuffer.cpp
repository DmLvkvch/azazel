#include "IndexBuffer.h"

#include "render/rhi/gl/GLESIndexBuffer.h"

namespace Azazel
{
    IndexBuffer::~IndexBuffer()
    {

    }
    
    IndexBuffer* IndexBuffer::create(const unsigned int* indices, size_t count)
    {
        return new GLESIndexBuffer(indices, count);
    }
}