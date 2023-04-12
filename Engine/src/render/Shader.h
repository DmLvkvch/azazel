#pragma once

#include <string>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>
#include "Texture.h"

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

        static constexpr char const* UNIFORM_TEXTURE0      = "u_texture_0";
        static constexpr char const* UNIFORM_TEXTURE1      = "u_texture_1";
        static constexpr char const* UNIFORM_TEXTURE2      = "u_texture_2";
        static constexpr char const* UNIFORM_TEXTURE3      = "u_texture_3";
        
        static constexpr char const* UNIFORM_MVP_MATRIX    = "u_mvp";
        static constexpr char const* UNIFORM_MODEL_MATRIX  = "u_model_matrix";
        static constexpr char const* UNIFORM_NORMAL_MATRIX = "u_normal_matrix";


        Shader(const std::string& vertexShader, const std::string& fragmentShader);

        virtual ~Shader();

        virtual void bind() const = 0;

        virtual void unbind() const = 0;
        
        virtual Shader* setFloat(const std::string& name, float value) = 0;

        virtual Shader* setInt(const std::string& name, int value) = 0;

        virtual Shader* setTexture(const std::string& name, const Texture& texture, int slot = 0) = 0;

        virtual Shader* setTextureCube(const std::string& name, const CubeMap& cubeMap, int slot = 0) = 0;

	    virtual Shader* setVec4f(const std::string& name, const glm::vec4& vec4) = 0;

        virtual Shader* setMatrix4f(const std::string& name, const glm::mat4& mvp) = 0;

        virtual Shader* setVec3f(const std::string& name, const glm::vec3& vec3) = 0;

        virtual Shader* setVec2f(const std::string& name, const glm::vec2& vec2) = 0;

        void setLabel(const std::string& label);

        const inline std::string& getLabel() const
        {
            return label;
        }

        static Shader* create(const std::string& vertexShader, const std::string& fragmentShader);
    private:
        std::string label;
    };
}