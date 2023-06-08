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
        
        const inline int getWidth() const
        {
            return width;
        }
        
        const inline int getHeight() const
        {
            return height;
        }

        virtual int getRendererID() const = 0;
        static RenderBuffer* create(int width, int height);
    private:
        int width;
        int height;
    };
}