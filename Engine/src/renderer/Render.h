#pragma once

#include "RenderApi.h"
#include <renderer/Texture.h>

#include <renderer/IndexBuffer.h>
#include <renderer/VertexArray.h>
#include <renderer/Shader.h>
#include <renderer/Texture.h>
#include "Camera.h"

namespace Azazel
{
    class Render
    {
    private:
        RenderApi* renderApi;
        static Render* render;

        Camera camera;

    public:
        Render();
        virtual ~Render();

        RenderApi* getRenderApi();
        static Render* getRenderer();
    
        void clear(bool color = true, bool depth = false, bool stencil = false);

        void setClearColor(const glm::vec4& color = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));

        void drawIndexed(const VertexArray& vertexArray, const IndexBuffer& indexBuffer, const Shader& shader, const Texture& texture);

        void reset();

        void setBlendFunc();

        void setBlendEquation();
        
        void beginScene();

        void endScene();

        void drawMesh();
    };
}