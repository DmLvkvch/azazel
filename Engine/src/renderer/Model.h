#pragma once

#include <vector>
#include "Mesh.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "Vertex.h"

namespace Azazel
{
    class Model
    {
    public:
        std::vector<MeshData::Texture> texturesLoaded;
        std::vector<Mesh<Vertex_P3_N3_T2>> meshes;
        std::string dir;
        void loadModel(std::string path);
        void processNode(aiNode *node, const aiScene *scene);
        Mesh<Vertex_P3_N3_T2> processMesh(aiMesh *mesh, const aiScene *scene);
        std::vector<MeshData::Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, std::string typeName);
        unsigned int TextureFromFile(const char *path, const std::string &directory, bool gamma);
    };
}