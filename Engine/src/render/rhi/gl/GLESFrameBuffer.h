#pragma once

#include "render/FrameBuffer.h"

namespace Azazel
{
    class GLESFrameBuffer : public FrameBuffer
    {
    public:
        GLESFrameBuffer(Texture* texture);
        GLESFrameBuffer(Texture* texture, FrameBufferTarget* depthTarget);
        GLESFrameBuffer(Texture* texture, Texture* depthTarget);
        ~GLESFrameBuffer();
        void bind() const override;
        void unbind() const override;
        void setDepthTarget(FrameBufferTarget* depthTarget) override;
        void setDepthTarget(Texture* depthTexture) override;

        void addColorAttachment(Texture* colorTarget, int slot = 0) override;
    private:
        unsigned int rendererID;
    };
}