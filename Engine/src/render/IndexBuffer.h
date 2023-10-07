#pragma once

namespace Azazel
{
    class IndexBuffer
    {
    public:
        virtual ~IndexBuffer();
        virtual void bind() const = 0;
        virtual void unbind() const = 0;
        virtual unsigned int getElementCount() const = 0;
        static IndexBuffer* create(const unsigned int* indices, unsigned int size);
    };
}