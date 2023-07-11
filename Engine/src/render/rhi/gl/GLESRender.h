#pragma once

#include "render/Render.h"

namespace Azazel
{

    class Mesh;

    class GLESRender : public Render
    {
    public:
        GLESRender();

        virtual ~GLESRender();

        void init() override;

        void reset() override;

        void saveState() override;
    
        void popState() override;

        void clear(bool color = true, bool depth = false, bool stencil = false) override;

        void setViewport(int x, int y, unsigned int width, unsigned int height) override;

        void setScissor(bool enable) override;
    
        void setScissor(int x, int y, int width, int height) override;

        void setClearColor(const glm::vec4& color = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f)) override;

        void setMultisample(bool enable) override;

        void setCullFace(bool enable) override;

        void setCullFaceMode(CullMode cullMode) override;

        void setFrontFace(CullFront cullFront) override;

        void setDepthTest(bool enable) override;

        void setDepthMask(bool enable) override;

        void setDepthFunc(CompareFunction compareFunction) override;

        void setStencilTest(bool enable) override;

        void setStencilMask(unsigned int mask) override;

        void setStencilFunc(CompareFunction compareFunction, int ref, unsigned int mask) override;

        void setStencilOp(StencilOperation sfail, StencilOperation dpfail, StencilOperation dppass) override;

        void setStencilOpSeparate(CullMode face, StencilOperation sfail, StencilOperation dpfail, StencilOperation dppass) override;

        void setBlend(bool enable) override;

        void drawIndexed(const VertexArray& vertexArray, const IndexBuffer& indexBuffer, const Shader& shader) override;

        void drawIndexedInstanced(const VertexArray& vertexArray, const IndexBuffer& indexBuffer, const Shader& shader, int instanceCount) override;

        void drawIndexedInstanced(const VertexArray& vertexArray, const IndexBuffer& indexBuffer, const Shader& shader, const Texture& texture, int instanceCount) override;

        void drawArrays(const VertexArray& vertexArray, const Shader& shader, const Texture& texture) override;

        void drawArrays(const VertexArray& vertexArray, const Shader& shader, int vertexCount) override;

        void setBlendFunc(BlendFunction sFactor, BlendFunction dFactor) override;

        void setBlendEquation(BlendEquation blendEquation) override;
        
        void setFramebufferSRGB(bool enable) override;

        void beginScene() override;

        void endScene() override;

    private:
        int drawCalls;
    };
}