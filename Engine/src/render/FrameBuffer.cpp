#include "FrameBuffer.h"

#ifdef AZAZEL_GL
#include "render/rhi/gl/GLESFrameBuffer.h"
#else
#include "render/rhi/vulkan/AZFramebuffer.h"
#endif

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
        return nullptr;// new AZFrameBuffer(texture, depthTarget);
        #endif
    }

    FrameBuffer* FrameBuffer::create(Texture* texture, Texture* depthTarget)
    {
        #ifdef AZAZEL_GL
        return new GLESFrameBuffer(texture, depthTarget);
        #else
        return nullptr;// new AZFrameBuffer(texture, depthTarget);
        #endif
    }

}