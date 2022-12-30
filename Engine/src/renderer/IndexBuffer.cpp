#include "IndexBuffer.h"

#include "rhi/gl/GLESIndexBuffer.h"

namespace Azazel
{
    IndexBuffer::~IndexBuffer()
    {

    }
    
    IndexBuffer* IndexBuffer::create(unsigned int* indices, size_t count)
    {
        return new GLESIndexBuffer(indices, count);
    }
}