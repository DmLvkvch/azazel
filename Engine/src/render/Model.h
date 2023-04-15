#pragma once

#include <vector>
#include <assimp/scene.h>
#include <memory>

#include "render/Mesh.h"
#include "render/Vertex.h"
#include "render/Shader.h"
#include "render/Transform.h"
#include "render/Texture.h"

namespace Azazel
{
    class Model
    {
    public:

        Model() = default;

        Model(const std::vector<Mesh<Vertex_P3_N3_T2>>& meshes);

        Model(Mesh<Vertex_P3_N3_T2>& mesh);

        Model(const std::string& path);

        Model(Model&& model)
        {
            this->meshes = std::move(model.meshes);
            this->textures = std::move(model.textures);
        }

        Model(const Model& model)
        {
            this->meshes = model.meshes;
            this->textures = model.textures;
        }

        void draw(Shader& shader);

        Model& operator=(const Model& model)
        {
            this->meshes = model.meshes;
            this->textures = model.textures;
            return *this;
        }

	    Model& operator=(Model&& model)
        {
            this->meshes = std::move(model.meshes);
            this->textures = std::move(model.textures);
            return *this;
        }

    public:
        Transform transform;

    private:

        void loadModel(const std::string& path);

        void processNode(aiNode* node, const aiScene* scene, const std::string& directory);

        Mesh<Vertex_P3_N3_T2> processMesh(aiMesh* mesh, const aiScene* scene, const std::string& directory);
    private:
        std::vector<Mesh<Vertex_P3_N3_T2>> meshes;
        std::vector<std::shared_ptr<Texture>> textures;
    };
}