#pragma once

#include <unordered_map>
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

		Shader(std::string vertexShader, std::string fragmentShader);

		virtual ~Shader();

		virtual int getShaderType(const ShaderType& shaderType) = 0;

		virtual unsigned int compile(const std::string& programCode, const ShaderType& shaderType) = 0;

		virtual void bind() const = 0;

		virtual void unbind() const = 0;
		
		virtual int getUniformLocation(const std::string& name) const = 0;

		virtual void setFloat(const std::string& name, float value) const = 0;

		virtual void setInt(const std::string& name, int value) const = 0;

		virtual void setVec4f(const std::string& name, float f0, float f1, float f2, float f3) const = 0;

		virtual void setMatrix4f(const std::string& name, const glm::mat4& mvp) const = 0;

		virtual void setVec3f(const std::string& name, const glm::vec3& vec3) const = 0;

		virtual void setVec3f(const std::string& name, float f0, float f1, float f2) const = 0;
	
		virtual void setVec2f(const std::string& name, float x, float y) const = 0;

		static Shader* create(std::string vertexShader, std::string fragmentShader);
	};
}