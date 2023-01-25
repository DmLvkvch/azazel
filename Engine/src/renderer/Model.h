#pragma once

#include <vector>
#include <renderer/Mesh.h>
#include <assimp/scene.h>
#include <renderer/Vertex.h>
#include <renderer/Shader.h>
#include <renderer/Transform.h>
#include <renderer/Texture.h>
#include <memory>

namespace Azazel
{
    class Model
    {
    public:        
        Model() = default;

        Model(std::vector<Mesh<Vertex_P3_N3_T2>> meshes);

        Model(const std::string& path);

        void draw(const Shader& shader);

        static Model cube();

        Transform transform;
    private:

        void loadModel(const std::string& path);

        void processNode(aiNode* node, const aiScene* scene);

        Mesh<Vertex_P3_N3_T2> processMesh(aiMesh* mesh, const aiScene* scene);
    private:
        std::string directory;
        std::vector<Mesh<Vertex_P3_N3_T2>> meshes;
        std::vector<std::shared_ptr<Texture>> textures;
    };
}