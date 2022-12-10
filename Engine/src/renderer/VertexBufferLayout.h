#pragma once

namespace Azazel
{
  //  class VertexBufferElement : VertexBufferElement
  //  {
  //  public:
  //      VertexBufferElement(unsigned int type, unsigned int count, unsigned int normalized)
  //      : VertexBufferElement(type, count, normalized)
  //      {
//
  //      }
//
  //      ~GLESVertexBufferElement()
  //      {
//
  //      }
//
  //      unsigned int getSizeOfType() const override
  //      {
  //          switch (type)
  //          {
  //              case GL_FLOAT: 
  //                  return sizeof(GLfloat);
  //              case GL_UNSIGNED_INT: 
  //                  return sizeof(GLuint);
  //              case GL_UNSIGNED_BYTE: 
  //                  return sizeof(GLbyte);
  //          }
  //          return 0;
  //      }
  //  };
//
  //  class GLESVertexBufferLayout : public VertexBufferLayout
  //  {
  //  protected:
  //      unsigned int stride;
  //      std::vector<VertexBufferElement> elements;
//
  //      void push(unsigned int type, unsigned int count, unsigned char normalized)
  //      {
  //          VertexBufferElement vbe {type, count, normalized};
  //          elements.push_back(vbe);
  //          stride += count * vbe.getSizeOfType();
  //      };
//
  //  public:
  //      GLESVertexBufferLayout() : stride(0) { }
  //      
  //      ~GLESVertexBufferLayout()
  //      {
//
  //      }
//
  //      void addFloat(unsigned int count)
  //      {
  //          this->add<float>(count);
  //      }
//
  //      void addInt(unsigned int count)
  //      {
  //          this->add<unsigned int>(count);
  //      }
//
  //      void addByte(unsigned int count)
  //      {
  //          this->add<unsigned char>(count);
  //      }
//
  //      template<typename T>
  //      void add(unsigned int count)
  //      {
//
  //      }
//
  //      template<>
  //      void add<float>(unsigned int count)
  //      { 
  //          push(GL_FLOAT, count, GL_FALSE); 
  //      }
//
  //      template<>
  //      void add<unsigned int>(unsigned int count)
  //      {
  //          push(GL_UNSIGNED_INT, count, GL_FALSE); 
  //      }
//
  //      template<>
  //      void add<unsigned char>(unsigned int count)
  //      {
  //          push(GL_UNSIGNED_BYTE, count, GL_TRUE); 
  //      }
//
  //      inline const std::vector<VertexBufferElement> getElements() const 
  //      { 
  //          return elements; 
  //      };
//
  //      inline unsigned int getStride() const 
  //      {
  //          return stride; 
  //      };
  //  };
}