#pragma once

#include <cstddef>

namespace Azazel
{
    enum class IndexBufferElementType
    {
        UNSIGNED_INT,
        UNSIGNED_SHORT
    };

    class IndexBuffer
    {
    public:
        virtual ~IndexBuffer();
        virtual void bind() const = 0;
        virtual void unbind() const = 0;
        virtual size_t getElementCount() const = 0;
        static IndexBuffer* create(const unsigned int* indices, size_t size);
    };
}