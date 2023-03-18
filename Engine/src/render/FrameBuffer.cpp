#include "FrameBuffer.h"

#include "render/rhi/gl/GLESFrameBuffer.h"

namespace Azazel
{
    FrameBuffer::~FrameBuffer()
    {

    }

    FrameBuffer* FrameBuffer::create(Texture* texture, FrameBufferTarget* depthTarget)
    {
        return new GLESFrameBuffer(texture, depthTarget);
    }

}