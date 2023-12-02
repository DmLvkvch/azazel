#include "AZFrameBuffer.h"

#include <iostream>

namespace Azazel
{
    VKFrameBuffer::VKFrameBuffer(Texture* texture)
    {
        
    }

    VKFrameBuffer::VKFrameBuffer(Texture* texture, FrameBufferTarget* depthTarget)
    {

    }

    VKFrameBuffer::~VKFrameBuffer()
    {
    }

    void VKFrameBuffer::bind() const
    {
    }
    
    void VKFrameBuffer::unbind() const
    {
    }

    void VKFrameBuffer::addColorAttachment(Texture* texture, int slot)
    {
        
    }

    void VKFrameBuffer::setDepthTarget(FrameBufferTarget* depthTarget)
    {

    }

    void VKFrameBuffer::setDepthTarget(Texture* depthTexture)
    {

    }
}