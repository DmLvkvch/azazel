#pragma once

#include "ShaderResourceManager.h"
#include "TextureResourceManager.h"
#include "ModelResourceManager.h"

namespace Azazel
{
    namespace ResourceManagers
    {
        inline static std::unique_ptr<TextureResourceManager> textureResourceManager (new TextureResourceManager());
        
        inline static std::unique_ptr < TextureDataResourceManager> textureDataResourceManager(new TextureDataResourceManager());

        inline static std::unique_ptr < ShaderResourceManager> shaderResourceManager(new ShaderResourceManager());

        inline static std::unique_ptr < ModelResourceManager> modelResourceManager ( new ModelResourceManager());
    }
}