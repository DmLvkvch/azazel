#include "VKFrameBuffer.h"
#include "vk_headers.h"

#include <iostream>

namespace Azazel
{
    VKFrameBuffer::VKFrameBuffer(std::shared_ptr<Texture> texture)
    {
        
    }

    VKFrameBuffer::VKFrameBuffer(std::shared_ptr<Texture> texture, std::shared_ptr<FrameBufferTarget> depthTarget)
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

    void VKFrameBuffer::addColorAttachment(std::shared_ptr<Texture> texture, int slot)
    {
        
    }

    void VKFrameBuffer::setDepthTarget(std::shared_ptr<FrameBufferTarget> depthTarget)
    {
        bind();
        // TODO
        unbind();
    }

    void VKFrameBuffer::setDepthTarget(std::shared_ptr<Texture> depthTexture)
    {
        bind();
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthTexture->getRendererId(), 0);
        unbind();
    }
}