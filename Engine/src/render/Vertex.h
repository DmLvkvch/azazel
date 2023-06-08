#pragma once

#include <vector>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include "VertexBuffer.h"

namespace Azazel
{
    enum class ElementType
    {
        FLOAT,
        HALF,
        BYTE,
        UNSIGNED_BYTE,
        INT,
        UNSIGNED_INT,
        SHORT,
        UNSIGNED_SHORT
    };

    // inline or static somewhere
    // int sizeOfElement(const ElementType& el)
    // {
    // 	switch (el)
    // 	{
    // 		case FLOAT:
    // 		case INT:
    // 		case UNSIGNED_INT:
    // 			return 4;
    // 		case BYTE:
    // 		case UNSIGNED_BYTE:
    // 			return 1;
    // 		case SHORT:
    // 		case UNSIGNED_SHORT:
    // 			return 2;
    // 		default:
    // 			return -1;
    // 	}
    // 	return -1;
    // }

    class Element
    {
    public:
        Semantic semantic;
        ElementType elementType;
        int dimension;
        int size;
        int offset;
        int id;

        Element(Semantic& semantic, int dimension, ElementType& elementType)
        {
            this->semantic = semantic;
            this->dimension = dimension;
            this->elementType = elementType;
        }
    };

    class Vertex
    {
    public:
        std::vector<Element>& elements;
        int size;

        Vertex(std::vector<Element>& elements)
        : elements(elements)
        {
            this->size = computeSize(elements);
        }
        virtual ~Vertex()
        {
            
        }
    private:
        int computeSize(const std::vector<Element>& elements)
        {
            int size = 0;
            for (auto& element : elements)
            {
                size += element.size;
            }
            return size;
        }
    };

    struct Vertex_P3_C4_T2
    {
    public:
        glm::vec3 position;
        glm::vec4 color;
        glm::vec2 texCoord;
        static BufferLayout bufferLayout;
        
        Vertex_P3_C4_T2() = default;
        
        Vertex_P3_C4_T2(glm::vec3 position, glm::vec4 color, glm::vec2 texCoord)
        : position(position), color(color), texCoord(texCoord)
        {

        }
    };

    struct Vertex_P3_T2
    {
    public:
        glm::vec3 position;
        glm::vec2 texCoord;
        static BufferLayout bufferLayout;
        
        Vertex_P3_T2() = default;

        Vertex_P3_T2(glm::vec3 position, glm::vec2 texCoord)
        : position(position), texCoord(texCoord)
        {

        }
    };

    struct Vertex_P3_N3_T2
    {
    public:
        glm::vec3 position;
        glm::vec3 normal;
        glm::vec2 texCoord;
        static BufferLayout bufferLayout;
        
        Vertex_P3_N3_T2() = default;

        Vertex_P3_N3_T2(glm::vec3 position, glm::vec3 normal, glm::vec2 texCoord)
        : position(position), normal(normal), texCoord(texCoord)
        {

        }

    };

    struct Vertex_P3_N3_T2_TAN3_BTAN_3
    {
    public:
        glm::vec3 position;
        glm::vec3 normal;
        glm::vec2 texCoord;
        glm::vec3 tangent;
        glm::vec3 bitangent;
        static BufferLayout bufferLayout;

        Vertex_P3_N3_T2_TAN3_BTAN_3() = default;

        Vertex_P3_N3_T2_TAN3_BTAN_3(glm::vec3 position, glm::vec3 normal, glm::vec2 texCoord, glm::vec3 tangent, glm::vec3 bitangent)
        : position(position), normal(normal), texCoord(texCoord), tangent(tangent), bitangent(bitangent)
        {

        }
    };

    struct Vertex_P3
    {
    public:
        glm::vec3 position;
        static BufferLayout bufferLayout;
        
        Vertex_P3() = default;
        Vertex_P3(glm::vec3 position) 
        : position(position)
        {

        }
    };
}