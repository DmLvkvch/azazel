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
    
        void clear(bool color = true, bool depth = false, bool stencil = false);

        void setClearColor(const glm::vec4& color = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));

        void drawIndexed(const VertexArray& vertexArray, const IndexBuffer& indexBuffer, const Shader& shader, const Texture& texture);

        void drawArrays(const VertexArray& vertexArray, const Shader& shader, const Texture& texture);

        void reset();

        void setBlendFunc();

        void setBlendEquation();
        
        void beginScene();

        void endScene();

        void drawMesh();
    };
}