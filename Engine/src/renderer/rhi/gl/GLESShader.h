#pragma once

#include <string>
#include <glm/glm.hpp>

namespace Azazel
{
	class GLESShader
	{
	private:
		unsigned int rendererId;

	public:

		enum ShaderType
		{
			VERTEX,
			FRAGMENT,
			GEOMETRY
		};

		GLESShader(std::string vertexShader, std::string fragmentShader);

		~GLESShader();

		int getShaderType(const ShaderType& shaderType);

		unsigned int compile(const std::string& programCode, const ShaderType& shaderType);

		void bind() const;

		void unbind() const;
		
		int getUniformLocation(const std::string& name);

		void setUniform1f(const std::string& name, float value);

		void setUniform1i(const std::string& name, int value);

		void setUniform4f(const std::string& name, float f0, float f1, float f2, float f3);

		void setMatrix4f(const std::string& name, const glm::mat4& mvp);

		void setVec3f(const std::string& name, const glm::vec3& vec3);
	};
}