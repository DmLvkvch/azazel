#pragma once

#include "RenderApi.h"
#include <renderer/rhi/TextureRHI.h>
#include <renderer/Texture.h>

#include <renderer/rhi/ShaderRHI.h>

namespace Azazel
{
    class Render
    {
    private:
        RenderApi* renderApi;
        static Render* render;
    public:
        Render();
        virtual ~Render();
        
        TextureRHI* createTextureRHI(const Texture* texture);

        RenderApi* getRenderApi();
        static Render* getCurrent();
    };
}