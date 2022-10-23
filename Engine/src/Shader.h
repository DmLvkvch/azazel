#pragma once

#include <string>
#include <glm/glm.hpp>

class Shader
{
private:
	std::string vertexShader;
	std::string fragmentShader;

	unsigned int rendererId;

public:

	enum ShaderType
	{
		VERTEX,
		FRAGMENT,
		GEOMETRY,
		UNKNOWN
	};

	Shader(std::string vertexShader, std::string fragmentShader);

	int getShaderType(ShaderType shaderType);

	unsigned int compile(const std::string& programCode, ShaderType shaderType);

	~Shader();

	void bind();

	void unbind();
	int getUniformLocation(const std::string& name);
	void setUniform1f(const std::string& name, float value);
	void setUniform1i(const std::string& name, int value);
	void setUniform4f(const std::string& name, float f0, float f1, float f2, float f3);
	void setMatrix4f(const std::string& name, const glm::mat4& mvp);
};