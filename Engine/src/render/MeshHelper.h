#pragma once

#include "render/Mesh.h"

namespace Azazel
{
    class MeshHelper
    {
    public:
        static Mesh genQuadMesh();
        static Mesh genSquareMesh();
        static Mesh genSphereMesh();
    };
}