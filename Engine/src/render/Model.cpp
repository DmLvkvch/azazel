#include "Model.h"

#include <iostream>
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include "TextureUtils.h"

namespace Azazel
{

    Model::Model(const std::string& path)
    {
        loadModel(path);
    }

    Model::Model(Mesh<Vertex_P3_N3_T2>& mesh)
    : meshes({mesh})
    {
        
    }

    Model::Model(const std::vector<Mesh<Vertex_P3_N3_T2>>& meshes)
    : meshes(meshes)
    {
        
    }

    void Model::loadModel(const std::string& path)
    {
        Assimp::Importer importer;
        const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_GenSmoothNormals);
        if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
        {
            std::cout << "ERROR::ASSIMP:: " << importer.GetErrorString() << std::endl;
            return;
        }
        std::string directory = path.substr(0, path.find_last_of('/'));
        processNode(scene->mRootNode, scene, directory);
    }

    void Model::draw(Shader& shader)
    {
        shader.bind();
        auto modelMatrix = transform.getTransformMatrix();
        shader.setMatrix4f("model", modelMatrix);
        shader.setMatrix4f("u_normal_matrix", glm::transpose(glm::inverse(glm::mat3(modelMatrix))));
        for (const auto& mesh : meshes)
        {
            for (int i = 0;i < mesh.textures.size(); i++)
            {
                std::string textureName = std::to_string(i);
                textureName = "u_texture_" + textureName;
                shader.setTexture(textureName, *mesh.textures[i], i);
            }    
            Render::getRender()->drawMesh(mesh, shader);
        }
    }

    void Model::processNode(aiNode* node, const aiScene* scene, const std::string& directory)
    {
        for(unsigned int i = 0; i < node->mNumMeshes; i++)
        {
            aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
            meshes.push_back(processMesh(mesh, scene, directory));
        }
        for(unsigned int i = 0; i < node->mNumChildren; i++)
        {
            processNode(node->mChildren[i], scene, directory);
        }
    }

    Mesh<Vertex_P3_N3_T2> Model::processMesh(aiMesh* mesh, const aiScene* scene, const std::string& directory)
    {
        std::vector<Vertex_P3_N3_T2> vertices;
        std::vector<unsigned int> indices;
        for(unsigned int i = 0; i < mesh->mNumVertices; i++)
        {
            Vertex_P3_N3_T2 vertex {};
            glm::vec3 vector { mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z };
            vertex.position = vector;
            if (mesh->HasNormals())
            {
                vector.x = mesh->mNormals[i].x;
                vector.y = mesh->mNormals[i].y;
                vector.z = mesh->mNormals[i].z;
                vertex.normal = vector;
            }
            if(mesh->mTextureCoords[0])
            {
                vertex.texCoord =  { mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y };
            }
            else
            {
                vertex.texCoord = { 0.0f, 0.0f };
            }
            vertices.push_back(vertex);
        }
        if(mesh->mMaterialIndex >= 0)
        {
            aiMaterial *material = scene->mMaterials[mesh->mMaterialIndex];
            int count = material->GetTextureCount(aiTextureType_DIFFUSE);
            for(unsigned int i = 0; i < count; i++)
            {
                aiString str;
                material->GetTexture(aiTextureType_DIFFUSE, i, &str);
                std::shared_ptr<Texture> texture;
                TextureData textureData;
                if (auto texture = scene->GetEmbeddedTexture(str.C_Str())) 
                {
                    if (texture->mHeight == 0)
                    {
                        textureData.data = stbi_load_from_memory(reinterpret_cast<unsigned char*>(texture->pcData), texture->mWidth, &textureData.width, &textureData.height, &textureData.bpp, 0);
                    }
                    else
                    {
                        textureData.data = stbi_load_from_memory(reinterpret_cast<unsigned char*>(texture->pcData), texture->mWidth * texture->mHeight, &textureData.width, &textureData.height, &textureData.bpp, 0);
                    }
                }
                else
                {
                    std::string fullPath = directory + "/" + str.C_Str();
                    textureData = TextureUtils::loadTexture(fullPath);
                }
                texture.reset(Texture::create(textureData));
                TextureUtils::freeTextureData(textureData);
                textures.push_back(texture);
           }
        }
        for (unsigned int i = 0; i < mesh->mNumFaces; i++)
        {
            aiFace face = mesh->mFaces[i];
            for (unsigned int j = 0; j < face.mNumIndices; j++)
            {
                indices.push_back(face.mIndices[j]);        
            }
        }
        auto m = Mesh<Vertex_P3_N3_T2>(vertices, indices);
        m.textures = std::move(textures);
        return m;
    }
}