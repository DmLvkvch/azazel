#pragma once

#include <renderer/rhi/TextureRHI.h>
#include <renderer/Texture.h>

namespace Azazel
{
    class RenderApi
    {
    public: 
        RenderApi();

        virtual ~RenderApi();
        virtual TextureRHI* createTextureRHI(const Texture* texture) = 0;
    };
}