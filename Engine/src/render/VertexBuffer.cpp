#include "VertexBuffer.h"

#ifdef AZAZEL_GL
#include "render/rhi/gl/GLESVertexBuffer.h"
#else 
#include "render/rhi/vulkan/VKVertexBuffer.h"
#endif

namespace Azazel
{
    VertexBuffer* VertexBuffer::create(const float* vertices, size_t size)
    {
        #ifdef AZAZEL_GL
        return new GLESVertexBuffer(vertices, size);
        #else 
        return nullptr; //VKVertexBuffer(vertices, size);
        #endif
    }
}