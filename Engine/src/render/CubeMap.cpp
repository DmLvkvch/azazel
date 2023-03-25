#include "CubeMap.h"

#include "render/rhi/gl/GLESCubeMap.h"
#include "render/rhi/vulkan/VKCubeMap.h"

namespace Azazel
{
    CubeMap::CubeMap()
    {
    }

    CubeMap::~CubeMap()
    {
    }
    
    CubeMap *CubeMap::create(std::array<TextureData, 6> textures)
    {
        #ifdef AZAZEL_GL
        return new GLESCubeMap(textures);
        #else 
        return new VKCubeMap();
        #endif
    }
}