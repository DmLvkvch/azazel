#pragma once

#include "render/VertexBuffer.h"

namespace Azazel
{
    class VKVertexBuffer : public VertexBuffer
    {
    public:
        VKVertexBuffer(const void* data, size_t size);
        ~VKVertexBuffer();
        void bind() const override;
        void unbind() const override;
        void setLayout(const BufferLayout& bufferlayout) override;
        void updateSubData(int offset, void* data, int size) override;
        const BufferLayout& getBufferLayout() const override;
    private:
        unsigned int rendererID;
        BufferLayout bufferLayout;
    };
}