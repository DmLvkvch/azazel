#pragma once

#include <renderer/VertexArray.h>
#include <renderer/VertexBuffer.h>

namespace Azazel
{
    class GLESVertexArray : public VertexArray
    {
    private:
        unsigned int rendererId;
        int lastIndex;
    public:
        GLESVertexArray();
        ~GLESVertexArray();
        void addBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer, const BufferLayout& layout) override;
        void bind() const override;
        void unbind() const override;
    };
}