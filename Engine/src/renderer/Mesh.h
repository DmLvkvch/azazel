#pragma once

#include <vector>

#include "Vertex.h"

#include <glm/glm.hpp>
#include <renderer/Shader.h>
#include <renderer/VertexArray.h>
#include <renderer/IndexBuffer.h>
#include <renderer/Texture.h>
#include <renderer/Render.h>
#include <memory>

namespace Azazel
{
    template<typename T>
    class Mesh
    {
    public:
        friend class Render;
        Mesh()
        {
        }

        Mesh(const std::vector<T>& vertices, const std::vector<unsigned int>& indices)
        {
            this->vertices = vertices;
            this->indices = indices;
            vertexArray.reset(VertexArray::create());
            indexBuffer.reset(IndexBuffer::create(indices.data(), indices.size()));
            std::shared_ptr<VertexBuffer> vb (VertexBuffer::create((float*) vertices.data(), vertices.size() * sizeof(T)));
            vertexArray->addBuffer(vb, T::bufferLayout);
        }

        void draw(Shader& shader)
        {
            shader.bind();
            shader.setInt("u_texture_0", 0);
            Render::getRender()->drawIndexed(*vertexArray, *indexBuffer, shader);
        }

        ~Mesh()
        {

        }

    private:
        std::shared_ptr<VertexArray> vertexArray;
        std::shared_ptr<IndexBuffer> indexBuffer;
        std::vector<T> vertices;
        std::vector<unsigned int> indices;
    };
}