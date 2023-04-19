#include "ResourceManager.h"
// #ifdef _DEBUG
// #define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
// #else
// #define DBG_NEW new
// #endif

namespace Azazel
{
    std::unique_ptr<TextureResourceManager> ResourceManagers::textureResourceManager(new TextureResourceManager());

    std::unique_ptr<TextureDataResourceManager> ResourceManagers::textureDataResourceManager(new TextureDataResourceManager());

    std::unique_ptr<ShaderResourceManager> ResourceManagers::shaderResourceManager(new ShaderResourceManager());

    std::unique_ptr<ModelResourceManager> ResourceManagers::modelResourceManager(new ModelResourceManager());
}