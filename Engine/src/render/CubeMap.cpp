#include "CubeMap.h"

#include "render/rhi/gl/GLESCubeMap.h"

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
        return new GLESCubeMap();
    }
}