#pragma once

#include "ShaderResourceManager.h"
#include "TextureResourceManager.h"
#include "ModelResourceManager.h"

namespace Azazel
{
    class ResourceManagers
    {
    public:

        static std::unique_ptr<TextureResourceManager> textureResourceManager;
        
        static std::unique_ptr<TextureDataResourceManager> textureDataResourceManager;

        static std::unique_ptr<ShaderResourceManager> shaderResourceManager;

        static std::unique_ptr<ModelResourceManager> modelResourceManager;
    };
}