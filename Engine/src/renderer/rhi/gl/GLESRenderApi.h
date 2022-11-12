#pragma once

#include <renderer/RenderApi.h>

namespace Azazel
{
    class GLESRenderApi : public RenderApi
    {
    public:
        TextureRHI* createTextureRHI(const Texture* texture) override;
    };
}