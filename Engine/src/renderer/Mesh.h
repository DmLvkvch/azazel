#pragma once

#include <vector>

#include "Vertex.h"

#include <glm/glm.hpp>
#include <renderer/Shader.h>
#include <renderer/VertexArray.h>
#include <renderer/IndexBuffer.h>

#include <memory>

namespace Azazel
{
    namespace MeshData
    {
        struct Texture
        {
            unsigned int id;
            std::string type;
        };
    }

    template<typename T>
    class Mesh
    {
    public:
        Mesh();
        Mesh(const std::vector<T>& vertices, const std::vector<unsigned int>& indices);
        ~Mesh();
        void draw(const Shader& shader);
    private:
        unsigned int VBO, EBO, VAO;
        std::shared_ptr<IndexBuffer> indexBuffer;
        std::shared_ptr<VertexArray> vertexArray;
        std::vector<T> vertices;
        std::vector<unsigned int> indices;
        std::vector<MeshData::Texture> textures;
    };
}