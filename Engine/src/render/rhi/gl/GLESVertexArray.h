#pragma once

#include "render/VertexArray.h"
#include "render/VertexBuffer.h"

namespace Azazel
{
    class GLESVertexArray : public VertexArray
    {
    public:
        GLESVertexArray();
        ~GLESVertexArray();
        void addBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer, const BufferLayout& layout) override;
        void bind() const override;
        void unbind() const override;
    private:
        unsigned int rendererID;
    };
}
