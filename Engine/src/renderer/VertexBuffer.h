#pragma once

#include <vector>

#include <string>

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
            case ShaderDataType::Float: return 4;
            case ShaderDataType::Float2: return 4 * 2;
            case ShaderDataType::Float3: return 4 * 3;
            case ShaderDataType::Float4: return 4 * 4;
            case ShaderDataType::Mat3: return 4 * 3 * 3;
            case ShaderDataType::Mat4: return 4 * 4 * 4;
            case ShaderDataType::Int: return 4;
            case ShaderDataType::Int2: return 4 * 2;
            case ShaderDataType::Int3: return 4 * 3;
            case ShaderDataType::Int4: return 4 * 4;
            case ShaderDataType::Bool: return 1;
        }
        return 0;
    }

    struct BufferElement
    {
        std::string name;
        ShaderDataType type;
        int size;
        int offset;

        BufferElement(ShaderDataType type,  const std::string& name)
        : name(name), type(type), size(shaderDataTypeSize(type)), offset(0)
        {

        }
    };

    class BufferLayout
    {
    public:
        inline const std::vector<BufferElement>& getElements() const
        {
            return elements;
        }
    private:
        std::vector<BufferElement> elements;
    };

    class VertexBuffer
    {
    public:
        virtual ~VertexBuffer() {}
        virtual void bind() const = 0;
        virtual void unbind() const = 0;
        static VertexBuffer* create(float* vertices, int size);
    };
}