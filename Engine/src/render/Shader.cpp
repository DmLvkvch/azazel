#include "Shader.h"

#ifdef AZAZEL_GL
#include "rhi/gl/GLESShader.h"
#else 
#endif
#include <string>

namespace Azazel
{
    Shader::Shader(const std::string& vertexShader, const std::string& fragmentShader)
    {  
        std::stoi()
    }

    Shader::~Shader()
    {

    }

    void Shader::setLabel(const std::string& label)
    {
        this->label = label;
    }

    Shader* Shader::create(const std::string& vertex, const std::string& fragment)
    {
        #ifdef AZAZEL_GL
        return new GLESShader(vertex, fragment);
        #else 
        return nullptr; // new AZShader(vertex, fragment);
        #endif
    }
}