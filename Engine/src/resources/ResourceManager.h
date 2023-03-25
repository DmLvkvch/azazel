#pragma once

#include "ShaderResourceManager.h"
#include "TextureResourceManager.h"

namespace Azazel
{
    namespace ResourceManagers
    {
        inline static TextureResourceManager* textureManager = new TextureResourceManager();
        
        inline static TextureDataResourceManager* textureDataManager = new TextureDataResourceManager();

        inline static ShaderResourceManager* shaderManager = new ShaderResourceManager();
    }
}