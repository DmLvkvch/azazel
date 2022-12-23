#include "FrameBuffer.h"

#include "rhi/gl/GLESFrameBuffer.h"

namespace Azazel
{
    FrameBuffer::~FrameBuffer()
    {

    }

    FrameBuffer* FrameBuffer::create(Texture* texture, FrameBufferTarget* frameBufferTarget)
    {
        return new GLESFrameBuffer(texture, frameBufferTarget);
    }

}