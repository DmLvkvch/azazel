#include "FrameBuffer.h"

#include "render/rhi/gl/GLESFrameBuffer.h"
#include "render/rhi/vulkan/VKFrameBuffer.h"

namespace Azazel
{
    FrameBuffer::~FrameBuffer()
    {

    }

    FrameBuffer* FrameBuffer::create(Texture* texture, FrameBufferTarget* depthTarget)
    {
        #ifdef AZAZEL_GL
        return new GLESFrameBuffer(texture, depthTarget);
        #else
        return new VKFrameBuffer(texture, depthTarget);
        #endif
    }

    FrameBuffer* FrameBuffer::create(Texture* texture, Texture* depthTarget)
    {
        #ifdef AZAZEL_GL
        return new GLESFrameBuffer(texture, depthTarget);
        #else
        return new VKFrameBuffer(texture, depthTarget);
        #endif
    }

}