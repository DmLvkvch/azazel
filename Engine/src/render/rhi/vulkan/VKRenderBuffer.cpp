#include "VKRenderBuffer.h"

#include "vk_headers.h"

namespace Azazel
{
    VKRenderBuffer::VKRenderBuffer(int width, int height)
    :RenderBuffer(width, height)
    {
    }

    VKRenderBuffer::~VKRenderBuffer()
    {
    }

    int VKRenderBuffer::getRendererID() const
    {
        return rendererID;
    }
    
    void VKRenderBuffer::bind() const
    {
    }

    void VKRenderBuffer::unbind() const
    {
    }
}
