#pragma once

#include <vector>
#include <stdexcept>
#include <string>

// TODO remove opengl dependency
#include "rhi/gl/gl_headers.h"

namespace Azazel
{
    enum class ShaderDataType
    {
        None, FLOAT, FLOAT2, FLOAT3, FLOAT4, 
        MAT3, MAT4, 
        INT, INT2, INT3, INT4,
        BOOL
    };

    enum class VertexBufferType
    {
        STATIC,
        DYNAMIC,
        STREAM
    };

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

    static int shaderDataTypeSize(ShaderDataType type)
    {
        switch(type)
        {
            case ShaderDataType::FLOAT:  return 4;
            case ShaderDataType::FLOAT2: return 4 * 2;
            case ShaderDataType::FLOAT3: return 4 * 3;
            case ShaderDataType::FLOAT4: return 4 * 4;
            case ShaderDataType::MAT3:   return 4 * 3 * 3;
            case ShaderDataType::MAT4:   return 4 * 4 * 4;
            case ShaderDataType::INT:    return 4;
            case ShaderDataType::INT2:   return 4 * 2;
            case ShaderDataType::INT3:   return 4 * 3;
            case ShaderDataType::INT4:   return 4 * 4;
            case ShaderDataType::BOOL:   return 1;
            case ShaderDataType::None:   throw std::invalid_argument("Invalid type None");
        }
        return 0;
    }

    // TODO remove opengl dependency
    static int shaderTypeToGLType(ShaderDataType type)
    {
        switch(type)
        {
            case ShaderDataType::FLOAT:  return GL_FLOAT;
            case ShaderDataType::FLOAT2: return GL_FLOAT;
            case ShaderDataType::FLOAT3: return GL_FLOAT;
            case ShaderDataType::FLOAT4: return GL_FLOAT;
            case ShaderDataType::MAT3:   return GL_FLOAT;
            case ShaderDataType::MAT4:   return GL_FLOAT;
            case ShaderDataType::INT:    return GL_INT;
            case ShaderDataType::INT2:   return GL_INT;
            case ShaderDataType::INT3:   return GL_INT;
            case ShaderDataType::INT4:   return GL_INT;
            case ShaderDataType::BOOL:   return GL_BOOL;
            case ShaderDataType::None:   throw std::invalid_argument("Invalid type None");
        }
        return 0;
    }

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
                case ShaderDataType::FLOAT:   return 1;
                case ShaderDataType::FLOAT2:  return 2;
                case ShaderDataType::FLOAT3:  return 3;
                case ShaderDataType::FLOAT4:  return 4;
                case ShaderDataType::MAT3:    return 3 * 3;
                case ShaderDataType::MAT4:    return 4 * 4;
                case ShaderDataType::INT:     return 1;
                case ShaderDataType::INT2:    return 2;
                case ShaderDataType::INT3:    return 3;
                case ShaderDataType::INT4:    return 4;
                case ShaderDataType::BOOL:    return 1;
                case ShaderDataType::None:    return 0;
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
        virtual void updateData(void* data, int size) = 0;
        
        static VertexBuffer* create(const float* vertices, size_t size);
    };
}