#pragma once

#include "Texture.h"
#include "FrameBufferTarget.h"
#include <memory>

namespace Azazel
{
    class FrameBuffer
    {
    public:
        FrameBuffer() = default;
        virtual ~FrameBuffer();
        virtual void bind() const = 0;
        virtual void unbind() const = 0;
        virtual void setDepthTarget(std::shared_ptr<FrameBufferTarget> depthTarget) = 0;
        virtual void addColorAttachment(std::shared_ptr<Texture> texture, int slot = 0) = 0;
        static FrameBuffer* create(std::shared_ptr<Texture> texture, std::shared_ptr<FrameBufferTarget> depthTarget);
    protected:
        std::shared_ptr<Texture> colorTextureTarget;
        std::shared_ptr<FrameBufferTarget> depthTarget;
    };
}