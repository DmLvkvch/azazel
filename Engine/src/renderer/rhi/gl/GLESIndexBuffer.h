#pragma once

#include "renderer/IndexBuffer.h"

namespace Azazel
{
    class GLESIndexBuffer : public IndexBuffer
    {
    public:
        GLESIndexBuffer(const void* data, size_t count);

        ~GLESIndexBuffer();

        void bind() const override;

        void unbind() const override;

        size_t getElementCount() const override;
    private:
        unsigned int rendererId;
        size_t count;
    };
}