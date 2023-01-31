#include "RenderBuffer.h"

#include "renderer/rhi/gl/GLESRenderBuffer.h"

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
        return new GLESRenderBuffer(width, height);
    }
}
