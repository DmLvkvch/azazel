#include "IndexBuffer.h"

#ifdef AZAZEL_GL
#include "render/rhi/gl/GLESIndexBuffer.h"
#else
#include "render/rhi/vulkan/VKIndexBuffer.h"
#endif
// #ifdef _DEBUG
// #define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
// #else
// #define DBG_NEW new
// #endif
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