#pragma once

#include "render/Texture.h"
#include "render/IndexBuffer.h"
#include "render/VertexArray.h"
#include "render/Shader.h"
#include "render/Texture.h"
#include "render/Vertex.h"
#include "camera/Camera.h"
#include "Types.h"
#include <memory>
#include "Mesh.h"

namespace Azazel
{
    struct RenderStats
    {
        int drawCalls = 0;
        int gpuMemoryUsage = 0;
        int trianglesCount = 0;

        void reset()
        {
            drawCalls = 0;
            gpuMemoryUsage = 0;
            trianglesCount = 0;
        }
    };

    struct Viewport
    {
        int x;
        int y;
        int width;
        int height;

        Viewport()
        : x(0), y(0), width(1280), height(720)
        {

        }

        Viewport(int x, int y, int width, int height)
        : x(x), y(y), width(width), height(height)
        {

        }
    };

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

        void setViewport(Viewport viewport)
        {
            setViewport(viewport.x, viewport.y, viewport.width, viewport.height);
        }

        virtual void popViewport() = 0;

        virtual void setScissor(bool enable) = 0;
    
        virtual void setScissor(int x, int y, int width, int height) = 0;

        virtual void setClearColor(const glm::vec4& color = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f)) = 0;

        virtual void setMultisample(bool enable) = 0;

        virtual void setCullFace(bool enable) = 0;

        virtual void setCullFaceMode(CullMode cullMode) = 0;

        virtual void setFrontFace(CullFront cullFront) = 0;

        virtual void setDepthTest(bool enable) = 0;

        virtual void setDepthMask(bool enable) = 0;

        virtual void setDepthFunc(CompareFunction compareFunction) = 0;

        virtual void setStencilTest(bool enable) = 0;

        virtual void setStencilMask(unsigned int mask) = 0;

        virtual void setStencilFunc(CompareFunction compareFunction, int ref, unsigned int mask) = 0;

        virtual void setStencilOp(StencilOperation sfail, StencilOperation dpfail, StencilOperation dppass) = 0;

        virtual void setStencilOpSeparate(CullMode face, StencilOperation sfail, StencilOperation dpfail, StencilOperation dppass) = 0;

        virtual void setBlend(bool enable) = 0;

        virtual void drawIndexed(const VertexArray& vertexArray, const IndexBuffer& indexBuffer, const Shader& shader) = 0;

        virtual void drawIndexedInstanced(const VertexArray& vertexArray, const IndexBuffer& indexBuffer, const Shader& shader, int instanceCount) = 0;

        virtual void drawIndexedInstanced(const VertexArray& vertexArray, const IndexBuffer& indexBuffer, const Shader& shader, const Texture& texture, int instanceCount) = 0;

        virtual void drawArrays(const VertexArray& vertexArray, const Shader& shader, const Texture& texture) = 0;
    
        virtual void drawArrays(const VertexArray& vertexArray, const Shader& shader, int vertexCount) = 0;

        void drawMesh(const Mesh& mesh, const Shader& shader, const Texture& texture)
        {
            drawIndexed(*mesh.vertexArray, *mesh.indexBuffer, shader);
        }

        void drawMesh(const Mesh& mesh, const Shader& shader)
        {
            drawIndexed(*mesh.vertexArray, *mesh.indexBuffer, shader);
        }

        virtual void drawRect()
        {
            
        }

        virtual void reset() = 0;

        virtual void setBlendFunc(BlendFunction sFactor, BlendFunction dFactor) = 0;

        virtual void setBlendEquation(BlendEquation blendEquation) = 0;
        
        virtual void setFramebufferSRGB(bool enable) = 0;

        virtual void beginScene() = 0;

        virtual void endScene() = 0;

        Camera* getCamera()
        {
            return camera;
        }

        void setCamera(Camera* camera)
        {
            this->camera = camera;
        }

    protected:
        static std::unique_ptr<Render> render;
        
        RenderStats renderStats;
        Camera* camera;
        std::vector<Viewport> viewportStack;

        Viewport defaultViewport;
    };
}