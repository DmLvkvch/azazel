#pragma once

#include <renderer/rhi/VertexBufferLayout.h>
#include <vector>
#include "gl_headers.h"

namespace Azazel
{
    struct VertexBufferElement
    {
        unsigned int type;
        unsigned int count;
        unsigned char normalized;

        static unsigned int getSizeOfType(unsigned int type)
        {
            switch (type)
            {
                case GL_FLOAT: 
                    return sizeof(GLfloat);
                case GL_UNSIGNED_INT: 
                    return sizeof(GLuint);
                case GL_UNSIGNED_BYTE: 
                    return sizeof(GLbyte);
            }
            return 0;
        }
    };

    class GLESVertexBufferLayout : public VertexBufferLayout
    {
    private:
        unsigned int stride;
        std::vector<VertexBufferElement> elements;

        void push(unsigned int type, unsigned int count, unsigned char normalized)
        {
            elements.push_back({ type, count, normalized });
            stride += count * VertexBufferElement::getSizeOfType(type);
        };

    public:
        GLESVertexBufferLayout() : stride(0) { }
        
        ~GLESVertexBufferLayout()
        {

        }

        template<typename T>
        void add(unsigned int count)
        {

        }

        template<>
        void add<float>(unsigned int count) 
        { 
            push(GL_FLOAT, count, GL_FALSE); 
        }

        template<>
        void add<unsigned int>(unsigned int count)
        {
            push(GL_UNSIGNED_INT, count, GL_FALSE); 
        }

        template<>
        void add<unsigned char>(unsigned int count)
        {
            push(GL_UNSIGNED_BYTE, count, GL_TRUE); 
        }

        inline const std::vector<VertexBufferElement> getElements() const 
        { 
            return elements; 
        };

        inline unsigned int getStride() const 
        {
            return stride; 
        };
    };
}