#pragma once

#include <vector>
#include <stdexcept>
#include <string>
#include "rhi/gl/gl_headers.h"

namespace Azazel
{
    enum class ShaderDataType
    {
        None, Float, Float2, Float3, Float4, 
        Mat3, Mat4, 
        Int, Int2, Int3, Int4,
        Bool
    };

    static int shaderDataTypeSize(ShaderDataType type)
    {
        switch(type)
        {
            case ShaderDataType::Float:  return 4;
            case ShaderDataType::Float2: return 4 * 2;
            case ShaderDataType::Float3: return 4 * 3;
            case ShaderDataType::Float4: return 4 * 4;
            case ShaderDataType::Mat3:   return 4 * 3 * 3;
            case ShaderDataType::Mat4:   return 4 * 4 * 4;
            case ShaderDataType::Int:    return 4;
            case ShaderDataType::Int2:   return 4 * 2;
            case ShaderDataType::Int3:   return 4 * 3;
            case ShaderDataType::Int4:   return 4 * 4;
            case ShaderDataType::Bool:   return 1;
            case ShaderDataType::None:   throw std::invalid_argument("Invalid type None");
        }
        return 0;
    }

    static int shaderTypeToGLType(ShaderDataType type)
    {
        switch(type)
        {
            case ShaderDataType::Float:  return GL_FLOAT;
            case ShaderDataType::Float2: return GL_FLOAT;
            case ShaderDataType::Float3: return GL_FLOAT;
            case ShaderDataType::Float4: return GL_FLOAT;
            case ShaderDataType::Mat3:   return GL_FLOAT;
            case ShaderDataType::Mat4:   return GL_FLOAT;
            case ShaderDataType::Int:    return GL_INT;
            case ShaderDataType::Int2:   return GL_INT;
            case ShaderDataType::Int3:   return GL_INT;
            case ShaderDataType::Int4:   return GL_INT;
            case ShaderDataType::Bool:   return GL_BOOL;
            case ShaderDataType::None:   throw std::invalid_argument("Invalid type None");
        }
        return 0;
    }

    enum Semantic
    {
        Position3D,
        Position2D,
        Color,
        Tex_Coord,
        Normal,
        Tangent,
        Bitangent,
        Ashift,
        Agamma
    };


    struct BufferElement
    {
        Semantic semantic;
        ShaderDataType type;
        int size;
        int offset;
        bool normalized;

        BufferElement(ShaderDataType type, Semantic semantic, bool normalized = false)
        : semantic(semantic), type(type), size(shaderDataTypeSize(type)), offset(0), normalized(normalized)
        {

        }

        int getComponentCount() const
        {
            switch (type)
            {
                case ShaderDataType::Float:  return 1;
                case ShaderDataType::Float2: return 2;
                case ShaderDataType::Float3: return 3;
                case ShaderDataType::Float4: return 4;
                case ShaderDataType::Mat3:   return 3 * 3;
                case ShaderDataType::Mat4:   return 4 * 4;
                case ShaderDataType::Int:    return 1;
                case ShaderDataType::Int2:   return 2;
                case ShaderDataType::Int3:   return 3;
                case ShaderDataType::Int4:   return 4;
                case ShaderDataType::Bool:   return 1;
                case ShaderDataType::None:   return 0;
            }
            return 0;
        }
    };

    class BufferLayout
    {
    public:
        BufferLayout() = default;

        BufferLayout(const std::initializer_list<BufferElement>& elements)
        : elements(elements)
        {
            calculateOffsetAndStride();
        }
        
        inline const std::vector<BufferElement>& getElements() const
        {
            return elements;
        }

        inline const int getStride() const
        {
            return stride;
        }

        inline const int getSize() const
        {
            return size;
        }

    private:
        void calculateOffsetAndStride()
        {
            int offset = 0;
            stride = 0;
            for (auto& element : elements)
            {
                element.offset = offset;
                offset += element.size;
                stride += element.size;
                size += element.size;
            }
        }
    private:
        std::vector<BufferElement> elements;
        int stride = 0;
        int size = 0;
    };

    class VertexBuffer
    {
    public:
        virtual ~VertexBuffer() {}
        virtual void bind() const = 0;
        virtual void unbind() const = 0;

        virtual void setLayout(const BufferLayout& bufferlayout) = 0;
        virtual const BufferLayout& getBufferLayout() const = 0;
        virtual void updateSubData(int offset, void* data, int size) = 0;
        
        static VertexBuffer* create(const float* vertices, size_t size);
    };
}