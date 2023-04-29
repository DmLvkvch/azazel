#include "Shader.h"

#ifdef AZAZEL_GL
#include "rhi/gl/GLESShader.h"
#else 
#include "rhi/vulkan/VKShader.h"
#endif

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
        #ifdef AZAZEL_GL
        return new GLESShader(vertex, fragment);
        #else 
        return new VKShader(vertex, fragment);
        #endif
    }
}