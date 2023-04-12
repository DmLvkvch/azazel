#pragma once

#include "render/RenderBuffer.h"

namespace Azazel
{
    class VKRenderBuffer : public RenderBuffer
    {
    public:
        VKRenderBuffer(int width, int height);
        ~VKRenderBuffer();
        
        int getRendererID() const override;
        void bind() const override;
        void unbind() const override;
    private:
        unsigned int rendererID;
    };
}