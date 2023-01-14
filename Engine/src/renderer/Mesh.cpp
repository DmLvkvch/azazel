#include "Mesh.h"

#include <vector>
#include "Vertex.h"

namespace Azazel
{
    Mesh::Mesh(const std::vector<float>& vertices, const std::vector<unsigned int>& indices)
    {
        
    }

    Mesh::~Mesh()
    {

    }

    Mesh Mesh::genCubeMesh(float x, float y, float z, float width, float height, float depth)
    {
        std::vector<float> vertices ;
        
        std::vector<unsigned int> indices {0, 1, 2, 0, 2, 3};

        return Mesh(vertices, indices);
    }

    Mesh Mesh::genCube(float size)
    {
        return genCubeMesh(1, 1, 1, 1, 1, 1);
    }
}