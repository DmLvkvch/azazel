#include "ResourceManager.h"

namespace Azazel
{
    TextureResourceManager* TextureResourceManager::textureManager = new TextureResourceManager();
    
    ShaderResourceManager* ShaderResourceManager::shaderManager = new ShaderResourceManager();
}