#include "Model.h"

#include <iostream>
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include "TextureUtils.h"
#include "api/file/FileUtils.h"
#include "Render.h"
#include <nlohmann/json.hpp>

namespace Azazel
{
    Model Model::createModel(const std::string& path, int i)
    {
        Model model;
        return model;
    }


    Model Model::createModel(const std::string& path)
    {
        Model model;
        model.loadModel(path);
        return model;
    }

    Model::Model(Mesh& mesh)
    : meshes({mesh})
    {
        
    }

    Model::Model(const std::vector<Mesh>& meshes)
    : meshes(meshes)
    {
        
    }

    void Model::loadModel(const std::string& path)
    {
        Assimp::Importer importer;
        const aiScene* scene = importer.ReadFile(path, aiProcessPreset_TargetRealtime_Quality);
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
            if (mesh.material)
            {
                auto m = mesh.material;
                m->applyProperties(shader);
            }
            Render::getRender()->drawMesh(mesh, shader);
        }
    }

    void Model::processNode(aiNode* node, const aiScene* scene, const std::string& directory)
    {
        meshes.reserve(meshes.size() + node->mNumMeshes);
        for(unsigned int i = 0; i < node->mNumMeshes; i++)
        {
            aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
            meshes.push_back(std::move(processMesh(mesh, scene, directory)));
        }
        for(unsigned int i = 0; i < node->mNumChildren; i++)
        {
            processNode(node->mChildren[i], scene, directory);
        }
    }

    Mesh Model::processMesh(aiMesh* mesh, const aiScene* scene, const std::string& directory)
    {
        std::vector<Vertex_P3_N3_T2_TAN3_BTAN_3> vertices;
        std::vector<unsigned int> indices;
        vertices.reserve(mesh->mNumVertices);
        for(unsigned int i = 0; i < mesh->mNumVertices; i++)
        {
            Vertex_P3_N3_T2_TAN3_BTAN_3 vertex {};
            glm::vec3 vector { mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z };
            vertex.position = vector;
            if (mesh->HasNormals())
            {
                vector.x = mesh->mNormals[i].x;
                vector.y = mesh->mNormals[i].y;
                vector.z = mesh->mNormals[i].z;
                vertex.normal = vector;

                vector.x = mesh->mTangents[i].x;
                vector.y = mesh->mTangents[i].y;
                vector.z = mesh->mTangents[i].z;
                vertex.tangent = vector;

                vector.x = mesh->mBitangents[i].x;
                vector.y = mesh->mBitangents[i].y;
                vector.z = mesh->mBitangents[i].z;
                vertex.bitangent = vector;
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
        Material mat{};
        if(mesh->mMaterialIndex >= 0)
        {
            aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
            loadTextures(scene, material, aiTextureType_DIFFUSE, textures, directory);
            MaterialProperty prop;
            prop.setValue(textures.at(0));
            mat.setProperty("u_texture_0", prop);
            loadTextures(scene, material, aiTextureType_NORMALS, textures, directory);
           // if (textures.size() > 1)
            if (false)
            {
                MaterialProperty prop;
                prop.setValue(textures.at(1));
                mat.setProperty("normal", prop);
                prop.setValue(true);
                mat.setProperty("hasNormal", prop);
            }
        }
        
        for (unsigned int i = 0; i < mesh->mNumFaces; i++)
        {
            aiFace face = mesh->mFaces[i];
            indices.reserve(indices.size() + face.mNumIndices);
            for (unsigned int j = 0; j < face.mNumIndices; j++)
            {
                indices.push_back(face.mIndices[j]);        
            }
        }
        auto m = Mesh::createMesh<Vertex_P3_N3_T2_TAN3_BTAN_3>(vertices, indices);
        m.textures = std::move(textures);
        m.material = mat;
        return m;
    }


    void Model::loadTextures(const aiScene* scene, aiMaterial* material,
                            aiTextureType textureType, std::vector<std::shared_ptr<Texture>>& textures, const std::string& directory)
    {
        int diffuseCount = material->GetTextureCount(textureType);
        for (unsigned int i = 0; i < diffuseCount; i++)
        {
            aiString str;
            material->GetTexture(textureType, i, &str);
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

}