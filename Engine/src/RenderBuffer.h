#pragma once

namespace Azazel
{
    class RenderBuffer
    {
    private:
        unsigned int rendererId;
    public:
        RenderBuffer(int width, int height);
        
        ~RenderBuffer();

        void bind();

        void unbind();
    };
}