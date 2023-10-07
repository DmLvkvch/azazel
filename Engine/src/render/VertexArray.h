#pragma once

#include "VertexBuffer.h"
#include <memory>

namespace Azazel
{
    class VertexArray
    {
    public:
        virtual ~VertexArray() {}
        virtual void bind() const = 0;
        virtual void unbind() const = 0;
        virtual void addBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer, const BufferLayout& layout) = 0;
        virtual void addBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer) {}

        const inline int getVertexSize() const
        {
            return size;
        }
        static VertexArray* create();
    protected:
        std::vector<std::shared_ptr<VertexBuffer>> vertexBuffers;
        int size = 0;
    };
}