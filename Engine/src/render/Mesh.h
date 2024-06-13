#pragma once


#include "Vertex.h"
#include "render/VertexArray.h"
#include "render/IndexBuffer.h"
#include "render/Texture.h"
#include "Material.h"
#include <memory>
#include <vector>
#include <optional>

namespace Azazel
{
    class Mesh
    {
    public:
        friend class Render;
        
        Mesh()
        {
        }

        template<typename T>
        static Mesh createMesh(const std::vector<T>& vertices, const std::vector<unsigned int>& indices)
        {
            Mesh mesh;
            mesh.init<T>((float*) vertices.data(), vertices.size() * sizeof(T), indices.data(), indices.size());
            return mesh;
        }

        template<typename T>
        static Mesh createMesh(const std::vector<float>& vertices, const std::vector<unsigned int>& indices)
        {
            Mesh mesh;
            mesh.init<T>((float*) vertices.data(), vertices.size() * sizeof(float), indices.data(), indices.size());
            return mesh;
        }

        template<typename T>
        void init(const float* vertices, size_t size, const unsigned int* indices, size_t count)
        {
            vertexArray.reset(VertexArray::create());
            indexBuffer.reset(IndexBuffer::create(indices, count));
            std::shared_ptr<VertexBuffer> vertexBuffer (VertexBuffer::create(vertices, size));
            vertexArray->addBuffer(vertexBuffer, T::bufferLayout);
        }

        ~Mesh()
        {

        }

        std::optional<Material> material = std::nullopt;
    public:
        std::shared_ptr<VertexArray> vertexArray;
        std::shared_ptr<IndexBuffer> indexBuffer;
    };
}
