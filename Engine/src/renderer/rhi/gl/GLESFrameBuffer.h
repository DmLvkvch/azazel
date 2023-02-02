#pragma once

#include "renderer/FrameBuffer.h"

namespace Azazel
{
    class GLESFrameBuffer : public FrameBuffer
    {
    public:
        GLESFrameBuffer(std::shared_ptr<Texture> texture);
        GLESFrameBuffer(std::shared_ptr<Texture> texture, std::shared_ptr<FrameBufferTarget> depthTarget);
        ~GLESFrameBuffer();
        void bind() const override;
        void unbind() const override;
        void setDepthTarget(std::shared_ptr<FrameBufferTarget> depthTarget) override;
        void setDepthTarget(std::shared_ptr<Texture> depthTexture) override;

        void addColorAttachment(std::shared_ptr<Texture> colorTarget, int slot = 0) override;
    private:
        unsigned int rendererId;
    };
}