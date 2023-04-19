#include "Shader.h"

#ifdef AZAZEL_GL
#include "rhi/gl/GLESShader.h"
#else 
#include "rhi/vulkan/VKShader.h"
#endif

// #ifdef _DEBUG
// #define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
// #else
// #define DBG_NEW new
// #endif

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