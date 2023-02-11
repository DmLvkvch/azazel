#include "VertexArray.h"

#include "render/rhi/gl/GLESVertexArray.h"

namespace Azazel
{
    VertexArray* VertexArray::create()
    {
        return new GLESVertexArray();
    }
}