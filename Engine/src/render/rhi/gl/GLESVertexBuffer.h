#pragma once

#include "render/VertexBuffer.h"

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
        void updateSubData(int offset, void* data, int size) override;
        const BufferLayout& getBufferLayout() const override;
    private:
        unsigned int rendererID;
        BufferLayout bufferLayout;
    };
}