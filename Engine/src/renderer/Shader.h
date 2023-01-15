#pragma once

#include <string>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>

namespace Azazel
{
    class Shader
    {
    public:

        enum ShaderType
        {
            VERTEX,
            FRAGMENT,
            GEOMETRY
        };

        Shader(const std::string& vertexShader, const std::string& fragmentShader);

        virtual ~Shader();

        virtual unsigned int compile(const std::string& programCode, const ShaderType& shaderType) = 0;

        virtual void bind() const = 0;

        virtual void unbind() const = 0;
        
        virtual int getUniformLocation(const std::string& name) const = 0;

        virtual Shader* setFloat(const std::string& name, float value) = 0;

        virtual Shader* setInt(const std::string& name, int value) = 0;

	    virtual Shader* setVec4f(const std::string& name, const glm::vec4& vec4) = 0;

        virtual Shader* setMatrix4f(const std::string& name, const glm::mat4& mvp) = 0;

        virtual Shader* setVec3f(const std::string& name, const glm::vec3& vec3) = 0;

        virtual Shader* setVec2f(const std::string& name, const glm::vec2& vec2) = 0;

        static Shader* create(const std::string& vertexShader, const std::string& fragmentShader);
    };
}