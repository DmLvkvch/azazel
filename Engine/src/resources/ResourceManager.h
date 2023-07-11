#pragma once

#include "ShaderResourceManager.h"
#include "TextureResourceManager.h"
#include "ModelResourceManager.h"

namespace Azazel
{
    class ResourceManagers
    {
    public:

        static TextureResourceManager& getTextureResourceManager()
        {
            static TextureResourceManager textureResourceManager;
            return textureResourceManager;
        }

        static TextureDataResourceManager& getTextureDataResourceManager()
        {
            static TextureDataResourceManager textureDataResourceManager;
            return textureDataResourceManager;
        }

        static ShaderResourceManager& getShaderResourceManager()
        {
            static ShaderResourceManager shaderResourceManager;
            return shaderResourceManager;
        }

        static ModelResourceManager& getModelResourceManager()
        {
            static ModelResourceManager modelResourceManager;
            return modelResourceManager;
        }
    };
}