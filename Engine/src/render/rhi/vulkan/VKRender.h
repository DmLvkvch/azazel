#pragma once

#include "render/Render.h"

namespace Azazel
{

    template <class T>
    class Mesh;

    class VKRender : public Render
    {
    public:
        VKRender();

        virtual ~VKRender();

        void init();

        void saveState();
    
        void popState();

        void clear(bool color = true, bool depth = false, bool stencil = false);

        void setViewport(int x, int y, int width, int height);

        void setScissor(bool enable);
    
        void setScissor(int x, int y, int width, int height);

        void setClearColor(const glm::vec4& color = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));

        void setMultisample(bool enable);

        void setCullFace(bool enable);

        void setCullFaceMode(CullMode cullMode);

        void setFrontFace(CullFront cullFront);

        void setDepthTest(bool enable);

        void setStencilTest(bool enable);

        void setBlend(bool enable);

        void drawIndexed(const VertexArray& vertexArray, const IndexBuffer& indexBuffer, const Shader& shader);

        void drawIndexed(const VertexArray& vertexArray, const IndexBuffer& indexBuffer, const Shader& shader, const Texture& texture);

        void drawArrays(const VertexArray& vertexArray, const Shader& shader, const Texture& texture);

        void reset();

        void setBlendFunc(BlendFunction sFactor, BlendFunction dFactor);

        void setBlendEquation(BlendEquation blendEquation);
        
        void beginScene();

        void endScene();

        void setCamera();
    private:
        int drawCalls;
    };
}