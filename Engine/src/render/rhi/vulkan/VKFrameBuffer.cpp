#include "VKFrameBuffer.h"
#include "vk_headers.h"

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
        bind();
        // TODO
        unbind();
    }

    void VKFrameBuffer::setDepthTarget(Texture* depthTexture)
    {
        bind();
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthTexture->getRendererId(), 0);
        unbind();
    }
}