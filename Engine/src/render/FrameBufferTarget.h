#pragma once

#include "Texture.h"
#include "RenderBuffer.h"

namespace Azazel
{
    class FrameBufferTarget
    {
    public:
        FrameBufferTarget() {}
        virtual ~FrameBufferTarget() {}

        template<typename T>
        bool checkTargetType()
        {
            return dynamic_cast<T*> (this) != nullptr;
        }
    };

    class FrameBufferTextureTarget : public FrameBufferTarget
    {
    public:
        FrameBufferTextureTarget(Texture* textureTarget) {}

        virtual ~FrameBufferTextureTarget() {}

    private:
        Texture* textureTarget;
    };

    class FrameBufferRenderBufferTarget : public FrameBufferTarget
    {
    public:
        FrameBufferRenderBufferTarget(RenderBuffer* renderBufferTarget) {}
        
        virtual ~FrameBufferRenderBufferTarget() {}
    private:
        RenderBuffer* renderBufferTarget;
    };
}