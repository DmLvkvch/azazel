#include "FrameBuffer.h"

#include <renderer/rhi/gl/GLESFrameBuffer.h>

namespace Azazel
{
    FrameBuffer::~FrameBuffer()
    {

    }

    FrameBuffer* FrameBuffer::create(std::shared_ptr<Texture> texture, std::shared_ptr<FrameBufferTarget> depthTarget)
    {
        return new GLESFrameBuffer(texture, depthTarget);
    }

}