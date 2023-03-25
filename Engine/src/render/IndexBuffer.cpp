#include "IndexBuffer.h"

#include "render/rhi/gl/GLESIndexBuffer.h"
#include "render/rhi/vulkan/VKIndexBuffer.h"

namespace Azazel
{
    IndexBuffer::~IndexBuffer()
    {

    }
    
    IndexBuffer* IndexBuffer::create(const unsigned int* indices, size_t count)
    {
        #ifdef AZAZEL_GL
        return new GLESIndexBuffer(indices, count);
        #else
        return new VKIndexBuffer(indices, count);
        #endif
    }
}