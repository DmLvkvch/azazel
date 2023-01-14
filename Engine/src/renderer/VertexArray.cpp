#include "VertexArray.h"

#include <renderer/rhi/gl/GLESVertexArray.h>

namespace Azazel
{
    VertexArray* VertexArray::create()
    {
        return new GLESVertexArray();
    }
}