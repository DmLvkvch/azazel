#include "ResourceManager.h"

namespace Azazel
{
    std::unique_ptr<TextureResourceManager> ResourceManagers::textureResourceManager(new TextureResourceManager());

    std::unique_ptr<TextureDataResourceManager> ResourceManagers::textureDataResourceManager(new TextureDataResourceManager());

    std::unique_ptr<ShaderResourceManager> ResourceManagers::shaderResourceManager(new ShaderResourceManager());

    std::unique_ptr<ModelResourceManager> ResourceManagers::modelResourceManager(new ModelResourceManager());
}