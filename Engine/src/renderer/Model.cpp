#include "Model.h"
#include <iostream>

namespace Azazel
{

    Model Model::cube()
    {
        std::vector<float> vertices
        {
            -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 0.0f, 0.0f,  
             0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 1.0f, 0.0f,  
             0.5f, 0.5f,  -0.5f,  0.0f,  0.0f, -1.0f, 1.0f, 1.0f,  
             0.5f, 0.5f,  -0.5f,  0.0f,  0.0f, -1.0f, 1.0f, 1.0f,  
            -0.5f, 0.5f,  -0.5f,  0.0f,  0.0f, -1.0f, 0.0f, 1.0f,  
            -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 0.0f, 0.0f,  

            -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,  0.0f, 0.0f,
             0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,  1.0f, 0.0f,
             0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,  1.0f, 1.0f,
             0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,  1.0f, 1.0f,
            -0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,  0.0f, 1.0f,
            -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,  0.0f, 0.0f,
 
            -0.5f,  0.5f,  0.5f, -1.0f,  0.0f, 0.0f,  0.0f, 0.0f,
            -0.5f,  0.5f, -0.5f, -1.0f,  0.0f, 0.0f,  1.0f, 0.0f,
            -0.5f, -0.5f, -0.5f, -1.0f,  0.0f, 0.0f,  1.0f, 1.0f,
            -0.5f, -0.5f, -0.5f, -1.0f,  0.0f, 0.0f,  1.0f, 1.0f,
            -0.5f, -0.5f,  0.5f, -1.0f,  0.0f, 0.0f,  0.0f, 1.0f,
            -0.5f,  0.5f,  0.5f, -1.0f,  0.0f, 0.0f,  0.0f, 0.0f,
 
            0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
            0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
            0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
            0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
            0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
            0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
 
            -0.5f, -0.5f, -0.5f,  0.0f, -1.0f, 0.0f,  0.0f, 0.0f,
             0.5f, -0.5f, -0.5f,  0.0f, -1.0f, 0.0f,  1.0f, 0.0f,
             0.5f, -0.5f,  0.5f,  0.0f, -1.0f, 0.0f,  1.0f, 1.0f,
             0.5f, -0.5f,  0.5f,  0.0f, -1.0f, 0.0f,  1.0f, 1.0f,
            -0.5f, -0.5f,  0.5f,  0.0f, -1.0f, 0.0f,  0.0f, 1.0f,
            -0.5f, -0.5f, -0.5f,  0.0f, -1.0f, 0.0f,  0.0f, 0.0f,
 
            -0.5f,  0.5f, -0.5f,  0.0f,  1.0f, 0.0f,  0.0f, 0.0f,
             0.5f,  0.5f, -0.5f,  0.0f,  1.0f, 0.0f,  1.0f, 0.0f,
             0.5f,  0.5f,  0.5f,  0.0f,  1.0f, 0.0f,  1.0f, 1.0f,
             0.5f,  0.5f,  0.5f,  0.0f,  1.0f, 0.0f,  1.0f, 1.0f,
            -0.5f,  0.5f,  0.5f,  0.0f,  1.0f, 0.0f,  0.0f, 1.0f,
            -0.5f,  0.5f, -0.5f,  0.0f,  1.0f, 0.0f,  0.0f, 0.0f
        };
        
        std::vector<unsigned int> indices;
        for (int i = 0; i < vertices.size(); i++)
        {
            indices.push_back(i);
        }

        Mesh<Vertex_P3_N3_T2> mesh(vertices, indices);
        std::vector<Mesh<Vertex_P3_N3_T2>> meshes {mesh};
        return Model(meshes);
    }

    Model::Model(const std::string& path)
    {
        loadModel(path);
    }

    Model::Model(std::vector<Mesh<Vertex_P3_N3_T2>> meshes)
    : meshes(meshes)
    {
        
    }

    void Model::draw(Shader& shader)
    {
        for (auto& mesh : meshes)
        {
            Render::getRender()->drawMesh(mesh, shader);
        }
    }

    void Model::loadModel(const std::string& path)
    {
        Assimp::Importer importer;
        const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs);
        if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
        {
            std::cout << "ERROR::ASSIMP:: " << importer.GetErrorString() << std::endl;
            return;
        }
        processNode(scene->mRootNode, scene);
    }

    void Model::processNode(aiNode* node, const aiScene* scene)
    {
        for(unsigned int i = 0; i < node->mNumMeshes; i++)
        {
            aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
            meshes.push_back(processMesh(mesh, scene));
        }
        for(unsigned int i = 0; i < node->mNumChildren; i++)
        {
            processNode(node->mChildren[i], scene);
        }
    }

    Mesh<Vertex_P3_N3_T2> Model::processMesh(aiMesh* mesh, const aiScene* scene)
    {
        std::vector<Vertex_P3_N3_T2> vertices;
        std::vector<unsigned int> indices;
        for(unsigned int i = 0; i < mesh->mNumVertices; i++)
        {
            Vertex_P3_N3_T2 vertex;
            glm::vec3 vector;
            vector.x = mesh->mVertices[i].x;
            vector.y = mesh->mVertices[i].y;
            vector.z = mesh->mVertices[i].z;
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
                glm::vec2 vec;
                vec.x = mesh->mTextureCoords[0][i].x; 
                vec.y = mesh->mTextureCoords[0][i].y;
                vertex.texCoord = vec;
            }
            else
            {
                vertex.texCoord = glm::vec2(0.0f, 0.0f);
            }
            vertices.push_back(vertex);
        }

        for(unsigned int i = 0; i < mesh->mNumFaces; i++)
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