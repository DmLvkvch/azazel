#pragma once

#include "ColorFormat.h"

#include "Texture.h"
#include "RenderBuffer.h"
#include <memory>

namespace Azazel
{
    class FrameBufferTarget
    {
    public:
        FrameBufferTarget(int width, int height, const ColorFormat& colorFormat);
        FrameBufferTarget();
        virtual ~FrameBufferTarget();
        virtual unsigned int getRendererId() = 0;
    };

    class FrameBufferTextureTarget
    {
    public:
        FrameBufferTextureTarget(std::shared_ptr<Texture> textureTarget);
        virtual ~FrameBufferTextureTarget();    
    private:
        std::shared_ptr<Texture> textureTarget;
    };

    class FrameBufferRenderBufferTarget
    {
    public:
        FrameBufferRenderBufferTarget(std::shared_ptr<RenderBuffer> renderBufferTarget);
        virtual ~FrameBufferRenderBufferTarget();    
    private:
        std::shared_ptr<RenderBuffer> renderBufferTarget;
    };
}