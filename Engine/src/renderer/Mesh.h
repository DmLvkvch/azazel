#pragma once

#include <vector>

#include "Vertex.h"

#include <glm/glm.hpp>
#include <renderer/Shader.h>

namespace Azazel
{
    namespace MeshData
    {
        struct Vertex
        {
            glm::vec3 Position;
            glm::vec3 Normal;
            glm::vec2 TexCoords;
        };
        struct Texture
        {
            unsigned int id;
            std::string type;
        };
    }
    class Mesh
    {
    private:
        std::vector<MeshData::Vertex> vertices;
        std::vector<unsigned int> indices;
        std::vector<MeshData::Texture> textures;
        glm::mat4 worldTransform;
    public:

        Mesh(const std::vector<float>& vertices, const std::vector<unsigned int>& indices);
        ~Mesh();
        static Mesh genCubeMesh(float x, float y, float z, float width, float height, float depth);
        static Mesh genCube(float size);

        void draw(const Shader& shader);
    };
}