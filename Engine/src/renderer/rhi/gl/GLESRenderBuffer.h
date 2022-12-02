#pragma once

namespace Azazel
{
    class GLESRenderBuffer 
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