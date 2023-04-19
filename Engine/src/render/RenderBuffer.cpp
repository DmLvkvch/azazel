#include "RenderBuffer.h"

#include "render/rhi/gl/GLESRenderBuffer.h"
#include "render/rhi/vulkan/VKRenderBuffer.h"
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

// #ifdef _DEBUG
// #define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
// #else
// #define DBG_NEW new
// #endif

namespace Azazel
{
    RenderBuffer::RenderBuffer(int width, int height)
    : width(width), height(height)
    {
    }

    RenderBuffer::~RenderBuffer()
    {
        
    }

    RenderBuffer* RenderBuffer::create(int width, int height)
    {
        #ifdef AZAZEL_GL
        return new GLESRenderBuffer(width, height);
        #else 
        return new VKRenderBuffer(width, height);
        #endif
    }
}
