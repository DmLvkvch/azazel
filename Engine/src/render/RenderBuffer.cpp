#include "RenderBuffer.h"

#include "render/rhi/gl/GLESRenderBuffer.h"
#include "render/rhi/vulkan/VKRenderBuffer.h"

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
