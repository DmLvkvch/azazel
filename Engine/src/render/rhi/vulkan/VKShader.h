#pragma once

#include "render/Shader.h"
#include <unordered_map>

namespace Azazel
{
    class VKShader : public Shader
    {
    public:

        VKShader(const std::string& vertexShader, const std::string& fragmentShader);

        ~VKShader();

        void bind() const override;

        void unbind() const override;
        
        Shader* setFloat(const std::string& name, float value) override;

        Shader* setInt(const std::string& name, int value) override;

	    Shader* setVec4f(const std::string& name, const glm::vec4& vec4) override;

        Shader* setMatrix4f(const std::string& name, const glm::mat4& mvp) override;

        Shader* setVec3f(const std::string& name, const glm::vec3& vec3) override;

        Shader* setVec2f(const std::string& name, const glm::vec2& vec2) override;

    private:
        int getShaderType(const ShaderType& shaderType) const;
        unsigned int compile(const std::string& programCode, const ShaderType& shaderType);

    private:
        unsigned int rendererID;
        std::unordered_map<std::string, int> uniformLocationMap;
    };
}