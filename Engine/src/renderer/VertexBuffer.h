#pragma once

namespace Azazel
{
    class VertexBuffer
    {
    public:
        virtual ~VertexBuffer() {}
        virtual void bind() = 0;
        virtual void unbind() = 0;

        static VertexBuffer* create(float* vertices, int size);
    };
}