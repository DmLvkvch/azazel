#pragma once

#include <renderer/rhi/ShaderRHI.h>
#include <unordered_map>

namespace Azazel
{
	class GLESShader : public ShaderRHI
	{
	private:
		unsigned int rendererId;
		std::unordered_map<std::string, int> uniformLocationMap;
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

		void bind();

		void unbind();
		
		int getUniformLocation(const std::string& name);

		void setUniform1f(const std::string& name, float value);

		void setUniform1i(const std::string& name, int value);

		void setUniform4f(const std::string& name, float f0, float f1, float f2, float f3);

		void setMatrix4f(const std::string& name, const glm::mat4& mvp);

		void setVec3f(const std::string& name, const glm::vec3& vec3);
	};
}