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
        void bind();
        void unbind();
    };
}