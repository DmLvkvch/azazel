#pragma once

namespace Azazel
{
    class IndexBuffer
    {
    public:
        virtual ~IndexBuffer(){}
        virtual void bind() const = 0;
        virtual void unbind() const = 0;
        virtual int getElementCount() const = 0;
        static IndexBuffer* create(unsigned int* indices, int size);
    };
}