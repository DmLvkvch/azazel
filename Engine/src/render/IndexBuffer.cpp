#include "IndexBuffer.h"

#ifdef AZAZEL_GL
#include "render/rhi/gl/GLESIndexBuffer.h"
#else
#include "render/rhi/vulkan/VKIndexBuffer.h"
#endif

namespace Azazel
{
    IndexBuffer::~IndexBuffer()
    {

    }
    
    IndexBuffer* IndexBuffer::create(const unsigned int* indices, unsigned int count)
    {
        #ifdef AZAZEL_GL
        return new GLESIndexBuffer(indices, count);
        #else
        return new VKIndexBuffer(indices, count);
        #endif
    }
}