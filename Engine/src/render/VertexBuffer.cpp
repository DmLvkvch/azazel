#include "VertexBuffer.h"

#ifdef AZAZEL_GL
#include "render/rhi/gl/GLESVertexBuffer.h"
#else 
#include "render/rhi/vulkan/VKVertexBuffer.h"
#endif

// #ifdef _DEBUG
// #define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
// #else
// #define DBG_NEW new
// #endif

namespace Azazel
{
    VertexBuffer* VertexBuffer::create(const float* vertices, size_t size)
    {
        #ifdef AZAZEL_GL
        return new GLESVertexBuffer(vertices, size);
        #else 
        return new VKVertexBuffer(vertices, size);
        #endif
    }
}