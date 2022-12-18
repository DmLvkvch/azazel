#include "RenderBuffer.h"

#include "rhi/gl/GLESRenderBuffer.h"

namespace Azazel
{
    RenderBuffer::RenderBuffer(int width, int height)
    : width(width), height(height)
    {
    }

    RenderBuffer::~RenderBuffer()
    {
    }

    int RenderBuffer::getWidth() const
    {
        return 0;
    }

    int RenderBuffer::getHeight() const
    {
        return 0;
    }

    int RenderBuffer::getRendererId() const
    {
        return 0;
    }

    RenderBuffer* RenderBuffer::create(int width, int height)
    {
        return nullptr;
    }
}
