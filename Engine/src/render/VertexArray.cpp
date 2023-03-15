#include "VertexArray.h"

#ifdef AZAZEL_GL
#include "rhi/gl/GLESVertexArray.h"
#else
#include "rhi/vulkan/VKVertexArray.h"
#endif

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