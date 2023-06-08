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

        virtual unsigned int getRendererID() = 0;

        template<typename T>
        bool checkTargetType()
        {
            return dynamic_cast<T*> (this) != nullptr;
        }
    };

    class FrameBufferTextureTarget : public FrameBufferTarget
    {
    public:
        FrameBufferTextureTarget(Texture* texture);

        virtual ~FrameBufferTextureTarget() {}

        virtual unsigned int getRendererID() override
        {
            return texture->getRendererID();
        }

    private:
        Texture* texture;
    };

    class FrameBufferRenderBufferTarget : public FrameBufferTarget
    {
    public:
        FrameBufferRenderBufferTarget(RenderBuffer* renderBuffer);
        
        virtual ~FrameBufferRenderBufferTarget() {}

        virtual unsigned int getRendererID() override
        {
            return renderBuffer->getRendererID();
        }
    private:
        RenderBuffer* renderBuffer;
    };
}