#pragma once

#include <renderer/Shader.h>
#include <unordered_map>

namespace Azazel
{
    class GLESShader : public Shader
    {
    private:
        unsigned int rendererId;
        std::unordered_map<std::string, int> uniformLocationMap;
    public:

        GLESShader(const std::string& vertexShader, const std::string& fragmentShader);

        ~GLESShader();

        int getShaderType(const ShaderType& shaderType) override;

        unsigned int compile(const std::string& programCode, const ShaderType& shaderType) override;

        void bind() const override;

        void unbind() const override;
        
        int getUniformLocation(const std::string& name) const override;

        void setFloat(const std::string& name, float value) const override;

        void setInt(const std::string& name, int value) const override;

	    void setVec4f(const std::string& name, const glm::vec4& vec4) const override;

        void setMatrix4f(const std::string& name, const glm::mat4& mvp) const override;

        void setVec3f(const std::string& name, const glm::vec3& vec3) const override;

        void setVec2f(const std::string& name, const glm::vec2& vec2) const override;

    };
}