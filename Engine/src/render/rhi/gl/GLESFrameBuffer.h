#pragma once

#include "render/FrameBuffer.h"
#include "GLESFrameBufferHistory.h"

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
        inline unsigned int getRendererId() const 
        {
            return rendererID;
        }
        void setDepthTarget(FrameBufferTarget* depthTarget) override;
        void setDepthTarget(Texture* depthTexture) override;
        void setDepthTarget(RenderBuffer* renderBuffer);
        void addColorAttachment(Texture* colorTarget, int slot = 0) override;
    private:
        int checkFrameBufferStatus();

        static FrameBufferHistory& frameBufferHistory()
        {
            static FrameBufferHistory fbh;
            return fbh;
        }
    private:
        unsigned int rendererID;
    };
}