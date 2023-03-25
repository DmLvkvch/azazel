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
    
    CubeMap *CubeMap::create()
    {
        #ifdef AZAZEL_GL
        return new GLESCubeMap();
        #else 
        return new VKCubeMap();
        #endif
    }
}