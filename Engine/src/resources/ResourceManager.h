#pragma once

#include "ShaderResourceManager.h"
#include "TextureResourceManager.h"
#include "ModelResourceManager.h"

namespace Azazel
{
    namespace ResourceManagers
    {
        inline static TextureResourceManager* textureResourceManager = new TextureResourceManager();
        
        inline static TextureDataResourceManager* textureDataResourceManager = new TextureDataResourceManager();

        inline static ShaderResourceManager* shaderResourceManager = new ShaderResourceManager();

        inline static ModelResourceManager* modelResourceManager = new ModelResourceManager();
    }
}