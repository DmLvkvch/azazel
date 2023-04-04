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

        static Mesh<Vertex_P3> genSkybox()
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

            return Mesh<Vertex_P3>(vertices, indices);
        }

        static Mesh<Vertex_P3_N3_T2> genCube()
        {
            std::vector<float> vertices
            {
                -0.5f, -0.5f, -0.5f,     0.0f,  0.0f, -1.0f,    0.0f, 0.0f,  
                 0.5f, -0.5f, -0.5f,     0.0f,  0.0f, -1.0f,    1.0f, 0.0f,  
                 0.5f, 0.5f,  -0.5f,     0.0f,  0.0f, -1.0f,    1.0f, 1.0f,  
                 0.5f, 0.5f,  -0.5f,     0.0f,  0.0f, -1.0f,    1.0f, 1.0f,  
                -0.5f, 0.5f,  -0.5f,     0.0f,  0.0f, -1.0f,    0.0f, 1.0f,  
                -0.5f, -0.5f, -0.5f,     0.0f,  0.0f, -1.0f,    0.0f, 0.0f,  

                -0.5f, -0.5f,  0.5f,     0.0f,  0.0f, 1.0f,     0.0f, 0.0f,
                 0.5f, -0.5f,  0.5f,     0.0f,  0.0f, 1.0f,     1.0f, 0.0f,
                 0.5f,  0.5f,  0.5f,     0.0f,  0.0f, 1.0f,     1.0f, 1.0f,
                 0.5f,  0.5f,  0.5f,     0.0f,  0.0f, 1.0f,     1.0f, 1.0f,
                -0.5f,  0.5f,  0.5f,     0.0f,  0.0f, 1.0f,     0.0f, 1.0f,
                -0.5f, -0.5f,  0.5f,     0.0f,  0.0f, 1.0f,     0.0f, 0.0f,

                -0.5f,  0.5f,  0.5f,     -1.0f,  0.0f, 0.0f,    0.0f, 0.0f,
                -0.5f,  0.5f, -0.5f,     -1.0f,  0.0f, 0.0f,    1.0f, 0.0f,
                -0.5f, -0.5f, -0.5f,     -1.0f,  0.0f, 0.0f,    1.0f, 1.0f,
                -0.5f, -0.5f, -0.5f,     -1.0f,  0.0f, 0.0f,    1.0f, 1.0f,
                -0.5f, -0.5f,  0.5f,     -1.0f,  0.0f, 0.0f,    0.0f, 1.0f,
                -0.5f,  0.5f,  0.5f,     -1.0f,  0.0f, 0.0f,    0.0f, 0.0f,

                 0.5f,  0.5f,  0.5f,     1.0f,  0.0f,  0.0f,    0.0f, 0.0f,
                 0.5f,  0.5f, -0.5f,     1.0f,  0.0f,  0.0f,    1.0f, 0.0f,
                 0.5f, -0.5f, -0.5f,     1.0f,  0.0f,  0.0f,    1.0f, 1.0f,
                 0.5f, -0.5f, -0.5f,     1.0f,  0.0f,  0.0f,    1.0f, 1.0f,
                 0.5f, -0.5f,  0.5f,     1.0f,  0.0f,  0.0f,    0.0f, 1.0f,
                 0.5f,  0.5f,  0.5f,     1.0f,  0.0f,  0.0f,    0.0f, 0.0f,

                -0.5f, -0.5f, -0.5f,     0.0f, -1.0f, 0.0f,     0.0f, 0.0f,
                 0.5f, -0.5f, -0.5f,     0.0f, -1.0f, 0.0f,     1.0f, 0.0f,
                 0.5f, -0.5f,  0.5f,     0.0f, -1.0f, 0.0f,     1.0f, 1.0f,
                 0.5f, -0.5f,  0.5f,     0.0f, -1.0f, 0.0f,     1.0f, 1.0f,
                -0.5f, -0.5f,  0.5f,     0.0f, -1.0f, 0.0f,     0.0f, 1.0f,
                -0.5f, -0.5f, -0.5f,     0.0f, -1.0f, 0.0f,     0.0f, 0.0f,

                -0.5f,  0.5f, -0.5f,     0.0f,  1.0f, 0.0f,     0.0f, 0.0f,
                 0.5f,  0.5f, -0.5f,     0.0f,  1.0f, 0.0f,     1.0f, 0.0f,
                 0.5f,  0.5f,  0.5f,     0.0f,  1.0f, 0.0f,     1.0f, 1.0f,
                 0.5f,  0.5f,  0.5f,     0.0f,  1.0f, 0.0f,     1.0f, 1.0f,
                -0.5f,  0.5f,  0.5f,     0.0f,  1.0f, 0.0f,     0.0f, 1.0f,
                -0.5f,  0.5f, -0.5f,     0.0f,  1.0f, 0.0f,     0.0f, 0.0f
            };
            
            std::vector<unsigned int> indices;
            int sz = vertices.size() / sizeof(Vertex_P3_N3_T2) * sizeof(float);
            indices.resize(sz);
            for (int i = 0; i < indices.size(); i++)
            {
                indices[i] = i;
            }

            return Mesh<Vertex_P3_N3_T2> (vertices, indices);
        }
    };
}