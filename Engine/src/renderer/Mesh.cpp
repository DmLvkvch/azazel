#include "Mesh.h"

#include <vector>
#include "Vertex.h"

#include <renderer/Render.h>

namespace Azazel
{
    
    template <typename T>
    Mesh<T>::Mesh(const std::vector<T>& vertices, const std::vector<unsigned int>& indices)
    {
        this->vertices = vertices;
        this->indices = indices;
    }

    template <typename T>
    Mesh<T>::~Mesh()
    {

    }

    template <typename T>
    void Mesh<T>::draw(const Shader& shader)
    {
    }
}