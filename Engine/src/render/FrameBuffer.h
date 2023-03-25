#pragma once

#include "Texture.h"
#include "FrameBufferTarget.h"
#include <array>

namespace Azazel
{
    class FrameBuffer
    {
    public:
        FrameBuffer() = default;
        virtual ~FrameBuffer();
        virtual void bind() const = 0;
        virtual void unbind() const = 0;
        virtual void addColorAttachment(Texture* texture, int slot = 0) = 0;
        virtual void setDepthTarget(Texture* depthTexture) = 0;
        virtual void setDepthTarget(FrameBufferTarget* depthTarget) = 0;
        static FrameBuffer* create(Texture* texture, FrameBufferTarget* depthTarget);
        static FrameBuffer* create(Texture* texture, Texture* depthTarget);
    protected:
        std::array<Texture*, 16> colorTextureTarget;
        FrameBufferTarget* depthTarget;
    };
}