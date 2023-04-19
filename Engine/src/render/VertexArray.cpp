#include "VertexArray.h"

#ifdef AZAZEL_GL
#include "rhi/gl/GLESVertexArray.h"
#else
#include "rhi/vulkan/VKVertexArray.h"
#endif

// #ifdef _DEBUG
// #define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
// #else
// #define DBG_NEW new
// #endif

namespace Azazel
{
    VertexArray* VertexArray::create()
    {
        #ifdef AZAZEL_GL
        return new GLESVertexArray();
        #else 
        return new VKVertexArray();
        #endif
    }
}