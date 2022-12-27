#pragma once

#include "RenderApi.h"
#include <renderer/Texture.h>

#include <renderer/rhi/gl/gl_headers.h>

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
        static Render* getCurrent();
    
        void clear(bool color = true, bool depth = false, bool stencil = false);

        void setClearColor(const glm::vec4& color);

        void setBlendFunc();

        void setBlendEquation();
        
        void beginScene();

        void endScene();

        void executeCommands();

        void drawMesh();
    };
}