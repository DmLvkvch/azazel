#pragma once

#include "rhi/IndexBufferRHI.h"

namespace Azazel
{
    class IndexBuffer
    {
    public:
        virtual ~IndexBuffer(){}
        virtual void bind() = 0;
        virtual void unbind() = 0;
        static IndexBuffer* create(unsigned int* indices, int size);
    };
}