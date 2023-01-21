#pragma once

#include <vector>
#include "Mesh.h"
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
        std::vector<MeshData::Texture> textures;
        std::vector<Mesh<Vertex_P3_N3_T2_TAN3_BTAN_3>> meshes;
        std::string dir;
        Model() = default;
        Model(const std::string& path)
        {
            loadModel(path);
        }
        void draw(Shader& shader)
        {

        }

        void loadModel(std::string path)
        {

        }

        void processNode(aiNode* node, const aiScene* scene)
        {

        }

        Mesh<Vertex_P3_N3_T2> processMesh(aiMesh* mesh, const aiScene* scene)
        {

        }

        std::vector<MeshData::Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName)
        {

        }

        unsigned int textureFromFile(const char* path, const std::string& directory, bool gamma)
        {

        }
    };
}