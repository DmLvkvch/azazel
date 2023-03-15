#pragma once

#include "render/FrameBuffer.h"

namespace Azazel
{
    class VKFrameBuffer : public FrameBuffer
    {
    public:
        VKFrameBuffer(std::shared_ptr<Texture> texture);
        VKFrameBuffer(std::shared_ptr<Texture> texture, std::shared_ptr<FrameBufferTarget> depthTarget);
        ~VKFrameBuffer();
        void bind() const override;
        void unbind() const override;
        void setDepthTarget(std::shared_ptr<FrameBufferTarget> depthTarget) override;
        void setDepthTarget(std::shared_ptr<Texture> depthTexture) override;

        void addColorAttachment(std::shared_ptr<Texture> colorTarget, int slot = 0) override;
    private:
        unsigned int rendererID;
    };
}