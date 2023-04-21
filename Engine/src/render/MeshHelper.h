#pragma once

#include "render/Mesh.h"
#include "render/Vertex.h"

namespace Azazel
{
    class MeshHelper
    {
    public:
        static Mesh genQuadMesh()
        {
            std::vector<float> vertices
            {
                -1.0f, -1.0f, 0.0f,   0.0f, 0.0f,
                1.0f, -1.0f, 0.0f,   1.0f, 0.0f,
                -1.0f, 1.0f, 0.0f,   0.0f, 1.0f,
                1.0f, 1.0f, 0.0f,   1.0f, 1.0f
            };

            std::vector<unsigned int> indices
            {
                0, 1, 3, 3, 2, 0
            };

            return Mesh::createMesh<Vertex_P3_T2>(vertices, indices);
        }

        static Mesh genSkybox()
        {
            std::vector<float> vertices
            {
                -1.0f,  1.0f, -1.0f,
                -1.0f, -1.0f, -1.0f,
                 1.0f, -1.0f, -1.0f,
                 1.0f, -1.0f, -1.0f,
                 1.0f,  1.0f, -1.0f,
                -1.0f,  1.0f, -1.0f,

                -1.0f, -1.0f,  1.0f,
                -1.0f, -1.0f, -1.0f,
                -1.0f,  1.0f, -1.0f,
                -1.0f,  1.0f, -1.0f,
                -1.0f,  1.0f,  1.0f,
                -1.0f, -1.0f,  1.0f,

                 1.0f, -1.0f, -1.0f,
                 1.0f, -1.0f,  1.0f,
                 1.0f,  1.0f,  1.0f,
                 1.0f,  1.0f,  1.0f,
                 1.0f,  1.0f, -1.0f,
                 1.0f, -1.0f, -1.0f,

                -1.0f, -1.0f,  1.0f,
                -1.0f,  1.0f,  1.0f,
                 1.0f,  1.0f,  1.0f,
                 1.0f,  1.0f,  1.0f,
                 1.0f, -1.0f,  1.0f,
                -1.0f, -1.0f,  1.0f,

                -1.0f,  1.0f, -1.0f,
                 1.0f,  1.0f, -1.0f,
                 1.0f,  1.0f,  1.0f,
                 1.0f,  1.0f,  1.0f,
                -1.0f,  1.0f,  1.0f,
                -1.0f,  1.0f, -1.0f,

                -1.0f, -1.0f, -1.0f,
                -1.0f, -1.0f,  1.0f,
                 1.0f, -1.0f, -1.0f,
                 1.0f, -1.0f, -1.0f,
                -1.0f, -1.0f,  1.0f,
                 1.0f, -1.0f,  1.0f  
            };
            
            std::vector<unsigned int> indices;
            size_t sz = vertices.size() / 3;
            indices.resize(sz);
            
            for (unsigned int i = 0; i < sz; i++)
            {
                indices[i] = i;
            }

            return Mesh::createMesh<Vertex_P3>(vertices, indices);
        }
    };
}