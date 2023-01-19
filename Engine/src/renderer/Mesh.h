#pragma once

#include <vector>

#include "Vertex.h"

#include <glm/glm.hpp>
#include <renderer/Shader.h>
#include <renderer/VertexArray.h>
#include <renderer/IndexBuffer.h>
#include <renderer/Render.h>
#include <memory>

namespace Azazel
{
    namespace MeshData
    {
        struct Texture
        {
            unsigned int id;
            std::string type;
        };
    }

    template<typename T>
    class Mesh
    {
    public:
    Mesh()
    {
        T t;
        BufferLayout  bl = t.bufferLayout;
    }

    Mesh(const std::vector<T>& vertices, const std::vector<unsigned int>& indices)
    {
        this->vertices = vertices;
        this->indices = indices;
        vertexArray.reset(VertexArray::create());
        indexBuffer.reset(IndexBuffer::create(indices.data(), indices.size()));
        std::shared_ptr<VertexBuffer> vb (VertexBuffer::create((float*) vertices.data(), vertices.size() * sizeof(T)));
        
        vertexArray->addBuffer(vb, T::bufferLayout);
        //glGenVertexArrays(1, &VAO);
        //glGenBuffers(1, &VBO);
        //glGenBuffers(1, &EBO);
        //
        //glBindVertexArray(VAO);
        //glBindBuffer(GL_ARRAY_BUFFER, VBO);
        //glBufferData(GL_ARRAY_BUFFER, vertices.size() * T::bufferLayout.getStride(), &vertices[0], GL_STATIC_DRAW);  
        //
        //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        //glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);
        //
        //glEnableVertexAttribArray(0);	
        //glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(T), (void*)0);
        //// vertex normals
        //glEnableVertexAttribArray(1);	
        //glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(T), (void*)12);
        //// vertex texture coords
        //glEnableVertexAttribArray(2);	
        //glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(T), (void*)24);
        //// vertex tangent
        //glEnableVertexAttribArray(3);
        //glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(T), (void*)32);
        //// vertex bitangent
        //glEnableVertexAttribArray(4);
        //glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(T), (void*)44);
        //
        //glBindVertexArray(0);
    }

    ~Mesh()
    {

    }

    void draw(const Shader& shader)
    {
        shader.bind();
        Render::getRender()->drawIndexed(*vertexArray, *indexBuffer, shader);
    }

    void draw(const Shader& shader, const Texture& texture)
    {
        shader.bind();
        Render::getRender()->drawIndexed(*vertexArray, *indexBuffer, shader, texture);
    }

    private:
        std::shared_ptr<VertexArray> vertexArray;
        std::shared_ptr<IndexBuffer> indexBuffer;
        std::vector<T> vertices;
        std::vector<unsigned int> indices;
        std::vector<MeshData::Texture> textures;
    };
}