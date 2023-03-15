#pragma once

#include "render/IndexBuffer.h"

namespace Azazel
{
    class VKIndexBuffer : public IndexBuffer
    {
    public:
        VKIndexBuffer(const void* data, size_t count);

        ~VKIndexBuffer();

        void bind() const override;

        void unbind() const override;

        size_t getElementCount() const override;
    private:
        unsigned int rendererID;
        size_t count;
    };
}