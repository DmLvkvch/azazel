#pragma once

#include "render/Texture.h"
#include "render/IndexBuffer.h"
#include "render/VertexArray.h"
#include "render/Shader.h"
#include "render/Texture.h"
#include "render/Vertex.h"
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

        virtual void init() = 0;

        virtual void saveState() = 0;
    
        virtual void popState() = 0;

        virtual void clear(bool color = true, bool depth = false, bool stencil = false) = 0;

        virtual void setViewport(int x, int y, int width, int height) = 0;

        virtual void setScissor(bool enable) = 0;
    
        virtual void setScissor(int x, int y, int width, int height) = 0;

        virtual void setClearColor(const glm::vec4& color = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f)) = 0;

        virtual void setMultisample(bool enable) = 0;

        virtual void setCullFace(bool enable) = 0;

        virtual void setCullFaceMode(CullMode cullMode) = 0;

        virtual void setFrontFace(CullFront cullFront) = 0;

        virtual void setDepthTest(bool enable) = 0;

        virtual void setStencilTest(bool enable) = 0;

        virtual void setBlend(bool enable) = 0;

        virtual void drawIndexed(const VertexArray& vertexArray, const IndexBuffer& indexBuffer, const Shader& shader) = 0;

        virtual void drawIndexed(const VertexArray& vertexArray, const IndexBuffer& indexBuffer, const Shader& shader, const Texture& texture) = 0;

        virtual void drawArrays(const VertexArray& vertexArray, const Shader& shader, const Texture& texture) = 0;

        template <typename T>
        void drawMesh(const Mesh<T>& mesh, const Shader& shader, const Texture& texture);

        template <typename T>
        void drawMesh(const Mesh<T>& mesh, const Shader& shader);

        virtual void reset() = 0;

        virtual void setBlendFunc(BlendFunction sFactor, BlendFunction dFactor) = 0;

        virtual void setBlendEquation(BlendEquation blendEquation) = 0;
        
        virtual void beginScene() = 0;

        virtual void endScene() = 0;

        void setCamera();
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