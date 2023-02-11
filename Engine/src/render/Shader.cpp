#include "Shader.h"

#include "render/rhi/gl/GLESShader.h"

namespace Azazel
{
    Shader::Shader(const std::string& vertexShader, const std::string& fragmentShader)
    {

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
        return new GLESShader(vertex, fragment);
    }
}