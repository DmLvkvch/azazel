#include "Shader.h"

#include "rhi/gl/GLESShader.h"

namespace Azazel
{
    Shader::Shader(std::string vertexShader, std::string fragmentShader)
    {

    }

    Shader::~Shader()
    {

    }

    Shader* Shader::create(std::string vertex, std::string fragment)
    {
        return new GLESShader(vertex, fragment);
    }
}