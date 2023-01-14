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
        FrameBufferTarget() {}
        virtual ~FrameBufferTarget() {}

        template<typename T>
        bool checkTarget()
        {
            return dynamic_cast<T*> (this) != nullptr;
        }
    };

    class FrameBufferTextureTarget : public FrameBufferTarget
    {
    public:
        FrameBufferTextureTarget(std::shared_ptr<Texture> textureTarget) {}
        virtual ~FrameBufferTextureTarget() {}
    private:
        std::shared_ptr<Texture> textureTarget;
    };

    class FrameBufferRenderBufferTarget : public FrameBufferTarget
    {
    public:
        FrameBufferRenderBufferTarget(std::shared_ptr<RenderBuffer> renderBufferTarget) {}
        virtual ~FrameBufferRenderBufferTarget() {}
    private:
        std::shared_ptr<RenderBuffer> renderBufferTarget;
    };
}