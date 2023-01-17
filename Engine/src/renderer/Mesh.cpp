#include "Mesh.h"

#include <vector>

#include <renderer/Render.h>
#include <iostream>
namespace Azazel
{
    template <typename T>
    Mesh<T>::Mesh()
    {
        T t;
        BufferLayout  bl = t.bufferLayout;
        std::cout<<sizeof(T)<<std::endl;
    }

    template <typename T>
    Mesh<T>::Mesh(const std::vector<T>& vertices, const std::vector<unsigned int>& indices)
    {
        this->vertices = vertices;
        this->indices = indices;
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glGenBuffers(1, &EBO);

        glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * T::bufferLayout.getStride(), &vertices[0], GL_STATIC_DRAW);  

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

        glEnableVertexAttribArray(0);	
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(T), (void*)0);
        // vertex normals
        glEnableVertexAttribArray(1);	
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(T), (void*)12);
        // vertex texture coords
        glEnableVertexAttribArray(2);	
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(T), (void*)24);
        // vertex tangent
        glEnableVertexAttribArray(3);
        glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(T), (void*)32);
        // vertex bitangent
        glEnableVertexAttribArray(4);
        glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(T), (void*)44);

        glBindVertexArray(0);
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