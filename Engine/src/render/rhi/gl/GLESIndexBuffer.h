#pragma once

#include "render/IndexBuffer.h"

namespace Azazel
{
    class GLESIndexBuffer : public IndexBuffer
    {
    public:
        GLESIndexBuffer(const void* data, unsigned int count);

        ~GLESIndexBuffer();

        void bind() const override;

        void unbind() const override;

        unsigned int getElementCount() const override;
    private:
        unsigned int rendererID;
        unsigned int count;
    };
}