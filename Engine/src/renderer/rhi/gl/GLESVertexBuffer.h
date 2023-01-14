#pragma once

#include <renderer/VertexBuffer.h>

namespace Azazel
{
    class GLESVertexBuffer : public VertexBuffer
    {
    public:
        GLESVertexBuffer(const void* data, size_t size);
        ~GLESVertexBuffer();
        void bind() const override;
        void unbind() const override;
        void setLayout(const BufferLayout& bufferlayout) override;
        void updateSubData(int offset, int size, void* data) override;
        const BufferLayout& getBufferLayout() const override;
    private:
        unsigned int rendererId;
        BufferLayout bufferLayout;
    };
}