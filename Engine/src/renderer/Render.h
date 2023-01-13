#pragma once

#include "RenderApi.h"
#include <renderer/Texture.h>

#include <renderer/IndexBuffer.h>
#include <renderer/VertexArray.h>
#include <renderer/Shader.h>
#include <renderer/Texture.h>
#include "Camera.h"
#include <memory>

namespace Azazel
{

    enum class CullMode
    {
        Front,
        Back,
        FrontAndBack,
        None
    };

    enum class BlendEquation
    {
        Add,
        Subtract,
        ReverseSubtract,
        Min,
        Max,
        None
    };

    enum class BlendFunction
    {
        Zero,
        One,
        SrcColor,
        OneMinusSrcColor,
        DstColor,
        OneMinusDstColor,
        SrcAlpha,
        OneMinusSrcAlpha,
        DstAlpha,
        OneMinusDstAlpha,
        ConstantColor,
        OneMinusConstantColor,
        ConstantAlpha,
        OneMinusConstantAlpha,
        SrcAlphaSaturate,
        None
    };

    enum class CompareFunction
    {
        Never,
        Less,
        Equal,
        LessOrEqual,
        Greater,
        NotEqual,
        GreaterOrEqual,
        Always,
    };

    class Render
    {
    private:
        static std::unique_ptr<Render> render;
        Camera camera;
        int drawCalls;
    public:
        Render();
        virtual ~Render();

        static Render* getRenderer();

        void init();

        void saveState();
    
        void popState();

        void clear(bool color = true, bool depth = false, bool stencil = false);

        void setViewport(int x, int y, int width, int height);

        void setScissor(bool enable);
    
        void setScissor(int x, int y, int width, int height);

        void setClearColor(const glm::vec4& color = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));

        void setBackFaceCulling(bool enable);

        void setDepthTest(bool enable);

        void setStencilTest(bool enable);

        void setBlend(bool enable);

        void drawIndexed(const VertexArray& vertexArray, const IndexBuffer& indexBuffer, const Shader& shader, const Texture& texture);

        void drawArrays(const VertexArray& vertexArray, const Shader& shader, const Texture& texture);

        void reset();

        void setBlendFunc(BlendFunction sFactor, BlendFunction dFactor);

        void setBlendEquation(BlendEquation blendEquation);
        
        void beginScene();

        void endScene();
    };
}