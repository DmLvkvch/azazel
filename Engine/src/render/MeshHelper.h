#pragma once

#include "render/Mesh.h"
#include "render/Vertex.h"

namespace Azazel
{
    class MeshHelper
    {
    public:
        static Mesh<Vertex_P3_T2> genQuadMesh()
        {
            std::vector<float> vertices
            {
                0.0f, 0.0f, 0.0f,   0.0f, 0.0f,
                1.0f, 0.0f, 0.0f,   1.0f, 0.0f,
                0.0f, 1.0f, 0.0f,   0.0f, 1.0f,
                1.0f, 1.0f, 0.0f,   1.0f, 1.0f
            };

            std::vector<unsigned int> indices
            {
                0, 1, 3, 3, 2, 0
            };

            return Mesh<Vertex_P3_T2>(vertices, indices);
        }
    };
}