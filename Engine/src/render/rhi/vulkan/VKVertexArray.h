#pragma once

#include "render/VertexArray.h"
#include "render/VertexBuffer.h"

namespace Azazel
{
    class VKVertexArray : public VertexArray
    {
    public:
        VKVertexArray();
        ~VKVertexArray();
        void addBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer, const BufferLayout& layout) override;
        void bind() const override;
        void unbind() const override;
    private:
        unsigned int rendererID;
    };
}
