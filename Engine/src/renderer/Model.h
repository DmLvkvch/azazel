#pragma once

#include <vector>
#include "Mesh.h"
#include <stb_image/stb_image.h>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "Vertex.h"
#include <renderer/Shader.h>

namespace Azazel
{
    class Model
    {
    public:
        std::vector<Mesh<Vertex_P3_N3_T2>> meshes;
        
        Model() = default;

        Model(std::vector<Mesh<Vertex_P3_N3_T2>> meshes);

        Model(const std::string& path);

        void draw(Shader& shader);

        void loadModel(const std::string& path);

        void processNode(aiNode* node, const aiScene* scene);

        Mesh<Vertex_P3_N3_T2> processMesh(aiMesh* mesh, const aiScene* scene);

        static Model cube();
    };
}