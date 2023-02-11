#pragma once


#include "Vertex.h"
#include "render/Shader.h"
#include "render/VertexArray.h"
#include "render/IndexBuffer.h"
#include "render/Texture.h"
#include "render/Render.h"
#include <memory>
#include <vector>

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
            init((float*) vertices.data(), vertices.size() * sizeof(T), indices.data(), indices.size());
        }

        Mesh(const std::vector<float>& vertices, const std::vector<unsigned int>& indices)
        {
            init((float*) vertices.data(), vertices.size() * sizeof(T), indices.data(), indices.size());
        }

        void init(const float* vertices, int size, const unsigned int* indices, int count)
        {
            vertexArray.reset(VertexArray::create());
            indexBuffer.reset(IndexBuffer::create(indices, count));
            std::shared_ptr<VertexBuffer> vb (VertexBuffer::create(vertices, size));
            vertexArray->addBuffer(vb, T::bufferLayout);
        }

        ~Mesh()
        {

        }

        void draw(Shader& shader)
        {
            Render::getRender()->drawIndexed(*vertexArray, *indexBuffer, shader);
        }

        std::vector<std::shared_ptr<Texture>>& getTextures()
        {
            return textures;
        }
    private:
        std::vector<std::shared_ptr<Texture>> textures;
        std::shared_ptr<VertexArray> vertexArray;
        std::shared_ptr<IndexBuffer> indexBuffer;
    };
}