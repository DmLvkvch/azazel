#pragma once

namespace Azazel
{
    class RenderBufferRHI
    {
    public:
        virtual ~RenderBufferRHI();
        virtual void bind() = 0;
        virtual void unbind() = 0;
        virtual int getWidth();
        virtual int getHeight();
    };
}