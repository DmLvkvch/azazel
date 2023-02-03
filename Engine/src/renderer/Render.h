#pragma once

#include "renderer/Texture.h"
#include "renderer/IndexBuffer.h"
#include "renderer/VertexArray.h"
#include "renderer/Shader.h"
#include "renderer/Texture.h"
#include "renderer/Vertex.h"
#include "camera/Camera.h"
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

    enum class CullFront
    {
        Cw,
        Ccw
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

    template <class T>
    class Mesh;

    class Render
    {
    public:
        Render();
        virtual ~Render();

        static Render* getRender();

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

        template <typename T>
        void drawMesh(const Mesh<T>& mesh, const Shader& shader, const Texture& texture);

        template <typename T>
        void drawMesh(const Mesh<T>& mesh, const Shader& shader);

        void reset();

        void setBlendFunc(BlendFunction sFactor, BlendFunction dFactor);

        void setBlendEquation(BlendEquation blendEquation);
        
        void beginScene();

        void endScene();
    private:
        static std::unique_ptr<Render> render;
        int drawCalls;
    };

    template <typename T> 
    void Render::drawMesh(const Mesh<T>& mesh, const Shader& shader, const Texture& texture)
    {
        drawIndexed(*mesh.vertexArray, *mesh.indexBuffer, shader, texture);
    }

    template <typename T> 
    void Render::drawMesh(const Mesh<T>& mesh, const Shader& shader)
    {
        drawIndexed(*mesh.vertexArray, *mesh.indexBuffer, shader);
    }
}