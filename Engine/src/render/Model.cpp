#include "Model.h"

#include <iostream>
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include "TextureUtils.h"

namespace Azazel
{
    Model Model::floor()
    {
        std::vector<float> vertices {
        // positions            // normals         // texcoords
         25.0f, -0.5f,  25.0f,  0.0f, 1.0f, 0.0f,  25.0f,  0.0f,
        -25.0f, -0.5f,  25.0f,  0.0f, 1.0f, 0.0f,   0.0f,  0.0f,
        -25.0f, -0.5f, -25.0f,  0.0f, 1.0f, 0.0f,   0.0f, 25.0f,

         25.0f, -0.5f,  25.0f,  0.0f, 1.0f, 0.0f,  25.0f,  0.0f,
        -25.0f, -0.5f, -25.0f,  0.0f, 1.0f, 0.0f,   0.0f, 25.0f,
         25.0f, -0.5f, -25.0f,  0.0f, 1.0f, 0.0f,  25.0f, 25.0f
        };
        std::vector<unsigned int> indices
        {
            0, 1, 2, 3, 4, 5
        };
        Mesh<Vertex_P3_N3_T2> mesh {vertices, indices};
        return Model(mesh);
    }

    Model Model::cube()
    {
        std::vector<float> vertices
        {
            -0.5f, -0.5f, -0.5f,     0.0f,  0.0f, -1.0f,    0.0f, 0.0f,  
             0.5f, -0.5f, -0.5f,     0.0f,  0.0f, -1.0f,    1.0f, 0.0f,  
             0.5f, 0.5f,  -0.5f,     0.0f,  0.0f, -1.0f,    1.0f, 1.0f,  
             0.5f, 0.5f,  -0.5f,     0.0f,  0.0f, -1.0f,    1.0f, 1.0f,  
            -0.5f, 0.5f,  -0.5f,     0.0f,  0.0f, -1.0f,    0.0f, 1.0f,  
            -0.5f, -0.5f, -0.5f,     0.0f,  0.0f, -1.0f,    0.0f, 0.0f,  

            -0.5f, -0.5f,  0.5f,     0.0f,  0.0f, 1.0f,     0.0f, 0.0f,
             0.5f, -0.5f,  0.5f,     0.0f,  0.0f, 1.0f,     1.0f, 0.0f,
             0.5f,  0.5f,  0.5f,     0.0f,  0.0f, 1.0f,     1.0f, 1.0f,
             0.5f,  0.5f,  0.5f,     0.0f,  0.0f, 1.0f,     1.0f, 1.0f,
            -0.5f,  0.5f,  0.5f,     0.0f,  0.0f, 1.0f,     0.0f, 1.0f,
            -0.5f, -0.5f,  0.5f,     0.0f,  0.0f, 1.0f,     0.0f, 0.0f,

            -0.5f,  0.5f,  0.5f,     -1.0f,  0.0f, 0.0f,    0.0f, 0.0f,
            -0.5f,  0.5f, -0.5f,     -1.0f,  0.0f, 0.0f,    1.0f, 0.0f,
            -0.5f, -0.5f, -0.5f,     -1.0f,  0.0f, 0.0f,    1.0f, 1.0f,
            -0.5f, -0.5f, -0.5f,     -1.0f,  0.0f, 0.0f,    1.0f, 1.0f,
            -0.5f, -0.5f,  0.5f,     -1.0f,  0.0f, 0.0f,    0.0f, 1.0f,
            -0.5f,  0.5f,  0.5f,     -1.0f,  0.0f, 0.0f,    0.0f, 0.0f,

            0.5f,  0.5f,  0.5f,      1.0f,  0.0f,  0.0f,    0.0f, 0.0f,
            0.5f,  0.5f, -0.5f,      1.0f,  0.0f,  0.0f,    1.0f, 0.0f,
            0.5f, -0.5f, -0.5f,      1.0f,  0.0f,  0.0f,    1.0f, 1.0f,
            0.5f, -0.5f, -0.5f,      1.0f,  0.0f,  0.0f,    1.0f, 1.0f,
            0.5f, -0.5f,  0.5f,      1.0f,  0.0f,  0.0f,    0.0f, 1.0f,
            0.5f,  0.5f,  0.5f,      1.0f,  0.0f,  0.0f,    0.0f, 0.0f,

            -0.5f, -0.5f, -0.5f,     0.0f, -1.0f, 0.0f,     0.0f, 0.0f,
             0.5f, -0.5f, -0.5f,     0.0f, -1.0f, 0.0f,     1.0f, 0.0f,
             0.5f, -0.5f,  0.5f,     0.0f, -1.0f, 0.0f,     1.0f, 1.0f,
             0.5f, -0.5f,  0.5f,     0.0f, -1.0f, 0.0f,     1.0f, 1.0f,
            -0.5f, -0.5f,  0.5f,     0.0f, -1.0f, 0.0f,     0.0f, 1.0f,
            -0.5f, -0.5f, -0.5f,     0.0f, -1.0f, 0.0f,     0.0f, 0.0f,

            -0.5f,  0.5f, -0.5f,     0.0f,  1.0f, 0.0f,     0.0f, 0.0f,
             0.5f,  0.5f, -0.5f,     0.0f,  1.0f, 0.0f,     1.0f, 0.0f,
             0.5f,  0.5f,  0.5f,     0.0f,  1.0f, 0.0f,     1.0f, 1.0f,
             0.5f,  0.5f,  0.5f,     0.0f,  1.0f, 0.0f,     1.0f, 1.0f,
            -0.5f,  0.5f,  0.5f,     0.0f,  1.0f, 0.0f,     0.0f, 1.0f,
            -0.5f,  0.5f, -0.5f,     0.0f,  1.0f, 0.0f,     0.0f, 0.0f
        };
        
        std::vector<unsigned int> indices;
        int sz = vertices.size() / sizeof(Vertex_P3_N3_T2) * sizeof(float);
        indices.resize(sz);
        for (int i = 0; i < indices.size(); i++)
        {
            indices[i] = i;
        }

        Mesh<Vertex_P3_N3_T2> mesh(vertices, indices);
        return Model({ mesh });
    }

    Model Model::sphere(float segmentsX, float segmentsY)
    {
        std::vector<Vertex_P3_N3_T2> vertices;
        vertices.reserve((segmentsX + 1) * (segmentsY + 1) * sizeof(Vertex_P3_N3_T2) / sizeof(float));
        for (unsigned int y = 0; y <= segmentsY; ++y)
        {
            for (unsigned int x = 0; x <= segmentsX; ++x)
            {
                float xSegment = (float)x / (float)segmentsX;
                float ySegment = (float)y / (float)segmentsY;
                constexpr float PI = glm::pi<float>();
                constexpr float TAU = glm::two_pi<float>();

                float xPos = std::cos(xSegment * TAU) * std::sin(ySegment * PI);
                float yPos = std::cos(ySegment * PI);
                float zPos = std::sin(xSegment * TAU) * std::sin(ySegment * PI);

                glm::vec3 pos { xPos, yPos, zPos };
                glm::vec2 texCoord { xSegment, ySegment };

                vertices.emplace_back(pos, pos, texCoord);
            }
        }
        std::vector<unsigned int> indices;
        indices.reserve(segmentsX * segmentsY * 6);
        for (int y = 0; y < segmentsY; ++y)
        {
            for (int x = 0; x < segmentsX; ++x)
            {
                indices.push_back((y + 1) * (segmentsX + 1) + x);
                indices.push_back(y * (segmentsX + 1) + x);
                indices.push_back(y * (segmentsX + 1) + x + 1);

                indices.push_back((y + 1) * (segmentsX + 1) + x);
                indices.push_back(y * (segmentsX + 1) + x + 1);
                indices.push_back((y + 1) * (segmentsX + 1) + x + 1);
            }
        }

        Mesh<Vertex_P3_N3_T2> mesh(vertices, indices);

        return Model({mesh});
    }

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

    void Model::draw( Shader& shader)
    {
        shader.bind();
        shader.setMatrix4f("model", transform.getTransformMatrix());
        for (const auto& mesh : meshes)
        {
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
                vertex.texCoord = glm::vec2 { mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y };
            }
            else
            {
                vertex.texCoord = glm::vec2(0.0f, 0.0f);
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
                std::string fullPath = directory +"/"+ str.C_Str();
                auto textureData = TextureUtils::loadTexture(fullPath);
                texture.reset(Texture::create(textureData));
                delete[] textureData.data;
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
        return Mesh<Vertex_P3_N3_T2>(vertices, indices);
    }
}