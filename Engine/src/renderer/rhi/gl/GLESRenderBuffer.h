#pragma once

#include <renderer/RenderBuffer.h>

namespace Azazel
{
    class GLESRenderBuffer : public RenderBuffer
    {
    private:
        unsigned int rendererId;
    public:
        GLESRenderBuffer(int width, int height);
        ~GLESRenderBuffer();
        
        int getRendererId() const override;
        void bind() const override;
        void unbind() const override;
    };
}