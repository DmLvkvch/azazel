#include "ResourceManager.h"

#include "ShaderResourceManager.h"

namespace Azazel
{
    TextureResourceManager* TextureResourceManager::textureManager = new TextureResourceManager();

    TextureDataResourceManager* TextureDataResourceManager::textureDataManager = new TextureDataResourceManager();
    
    ShaderResourceManager* ShaderResourceManager::shaderManager = new ShaderResourceManager();
}