#include "VertexArray.h"

#ifdef AZAZEL_GL
#include "rhi/gl/GLESVertexArray.h"
#endif

namespace Azazel
{
    VertexArray* VertexArray::create()
    {
        return nullptr;
    }
}