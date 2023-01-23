#include "Shader.h"

#include <renderer/rhi/gl/GLESShader.h>

namespace Azazel
{
    Shader::Shader(const std::string& vertexShader, const std::string& fragmentShader)
    : vertexCode(vertexShader), fragmentCode(fragmentShader)
    {

    }

    Shader::~Shader()
    {

    }

    Shader* Shader::create(const std::string& vertex, const std::string& fragment)
    {
        return new GLESShader(vertex, fragment);
    }
}