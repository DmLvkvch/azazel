#pragma once

#include "renderer/RenderBuffer.h"

namespace Azazel
{
    class GLESRenderBuffer : public RenderBuffer
    {
    public:
        GLESRenderBuffer(int width, int height);
        ~GLESRenderBuffer();
        
        int getRendererId() const override;
        void bind() const override;
        void unbind() const override;
    private:
        unsigned int rendererId;
    };
}