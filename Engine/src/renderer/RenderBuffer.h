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
        
        int getWidth()
        {
            return width;
        }
        
        int getHeight()
        {
            return height;
        }

        virtual int getRendererId() const;
        static RenderBuffer* create(int width, int height);
    private:
        int width;
        int height;
    };
}