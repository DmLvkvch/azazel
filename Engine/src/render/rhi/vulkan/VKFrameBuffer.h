#pragma once

#include "render/FrameBuffer.h"

namespace Azazel
{
    class VKFrameBuffer : public FrameBuffer
    {
    public:
        VKFrameBuffer(Texture* texture);
        VKFrameBuffer(Texture* texture, FrameBufferTarget* depthTarget);
        ~VKFrameBuffer();
        void bind() const override;
        void unbind() const override;
        void setDepthTarget(FrameBufferTarget* depthTarget) override;
        void setDepthTarget(Texture* depthTexture) override;

        void addColorAttachment(Texture* colorTarget, int slot = 0) override;
    private:
        unsigned int rendererID;
    };
}