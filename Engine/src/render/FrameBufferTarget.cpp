#include "FrameBufferTarget.h"

namespace Azazel
{

    FrameBufferTextureTarget::FrameBufferTextureTarget(Texture* texture)
    : texture(texture)
    {
    }

    FrameBufferRenderBufferTarget::FrameBufferRenderBufferTarget(RenderBuffer* renderBuffer)
    : renderBuffer(renderBuffer)
    {
    }
}