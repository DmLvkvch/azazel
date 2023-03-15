#pragma once

#include <vector>
#include <assimp/scene.h>
#include <memory>

#include "render/Mesh.h"
#include "render/Vertex.h"
#include "render/Shader.h"
#include "render/Transform.h"
#include "render/Texture.h"
#include <iostream>

namespace Azazel
{
    class Model
    {
    public:        
        Model() = default;

        Model(const std::vector<Mesh<Vertex_P3_N3_T2>>& meshes);

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

        void draw(const Shader& shader);

        static Model cube();

        Transform transform;

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

    private:

        void loadModel(const std::string& path);

        void processNode(aiNode* node, const aiScene* scene, const std::string& directory);

        Mesh<Vertex_P3_N3_T2> processMesh(aiMesh* mesh, const aiScene* scene, const std::string& directory);
    private:
        std::vector<Mesh<Vertex_P3_N3_T2>> meshes;
        std::vector<std::shared_ptr<Texture>> textures;
    };
}