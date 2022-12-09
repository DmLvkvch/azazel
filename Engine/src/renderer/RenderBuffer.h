#pragma once

namespace Azazel
{
    class RenderBuffer
    {
    public:
        RenderBuffer(int width, int height);
        virtual ~RenderBuffer();
        virtual void bind() const = 0;
        virtual void unbind() const = 0;
        int getWidth() const;
        int getHeight() const;
    };
}