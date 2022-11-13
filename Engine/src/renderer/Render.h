#pragma once

#include "RenderApi.h"
#include <renderer/rhi/TextureRHI.h>
#include <renderer/Texture.h>

#include <renderer/rhi/ShaderRHI.h>

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

        TextureRHI* createTextureRHI(const Texture* texture);

        RenderApi* getRenderApi();
        static Render* getCurrent();
    
        void clear();
        void drawMesh()
        {

        }

        void drawRect()
        {

        }
    };
}