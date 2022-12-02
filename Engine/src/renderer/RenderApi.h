#pragma once

#include <renderer/rhi/TextureRHI.h>
#include <renderer/rhi/ShaderRHI.h>
#include <renderer/rhi/IndexBufferRHI.h>
#include <renderer/rhi/VertexBufferRHI.h>
#include <renderer/rhi/FrameBufferRHI.h>

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