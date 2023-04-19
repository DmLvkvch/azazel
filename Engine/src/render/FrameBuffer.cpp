#include "FrameBuffer.h"

#ifdef AZAZEL_GL
#include "render/rhi/gl/GLESFrameBuffer.h"
#else
#include "render/rhi/vulkan/VKFrameBuffer.h"
#endif

//#ifdef _DEBUG
//#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
//#else
//#define DBG_NEW new
//#endif

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