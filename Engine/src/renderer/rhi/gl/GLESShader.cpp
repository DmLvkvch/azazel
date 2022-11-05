#include "GLESShader.h"

#include "gl_headers.h"

#include <iostream>

namespace Azazel
{
	GLESShader::GLESShader(std::string vertexShader, std::string fragmentShader)
	{
		unsigned int vertexShaderHandle = compile(vertexShader, VERTEX);
		unsigned int fragmentShaderHandle = compile(fragmentShader, FRAGMENT);

		rendererId = glCreateProgram();

		glAttachShader(rendererId, vertexShaderHandle);
		glAttachShader(rendererId, fragmentShaderHandle);
		glLinkProgram(rendererId);
		glDeleteShader(vertexShaderHandle);
		glDeleteShader(fragmentShaderHandle);

		int success;
		glGetProgramiv(rendererId, GL_LINK_STATUS, &success);
		char infoLog[512];
		if (!success) {
			glGetProgramInfoLog(rendererId, 512, NULL, infoLog);
			std::cout << "Shader creation error!\n" << infoLog << std::endl;
		}
	}

	GLESShader::~GLESShader()
	{
		glDeleteProgram(rendererId);
	}

	int GLESShader::getShaderType(const ShaderType& shaderType)
	{
		switch (shaderType)
		{
			case VERTEX:
				return GL_VERTEX_SHADER;
			case FRAGMENT:
				return GL_FRAGMENT_SHADER;
			case GEOMETRY:
				return GL_GEOMETRY_SHADER;
		}
		return -1;
	}

	unsigned int GLESShader::compile(const std::string& programCode, const ShaderType& shaderType)
	{
		unsigned int handle = glCreateShader(getShaderType(shaderType));
		const char* code = programCode.c_str();
		glShaderSource(handle, 1, &code, nullptr);
		glCompileShader(handle);
		return handle;
	}

	void GLESShader::bind() const
	{
		glUseProgram(rendererId);
	}

	void GLESShader::unbind() const
	{
		glUseProgram(0);
	}

	int GLESShader::getUniformLocation(const std::string& name)
	{
		int location = glGetUniformLocation(rendererId, name.c_str());
		if (location == -1)
		{
			std::cout << "No active uniform variable with name " << name << " found" << std::endl;
		}
		return location;
	}

	void GLESShader::setUniform1f(const std::string& name, float value)
	{
		glUniform1f(getUniformLocation(name), value);
	}

	void GLESShader::setUniform4f(const std::string& name, float f0, float f1, float f2, float f3)
	{
		glUniform4f(getUniformLocation(name), f0, f1, f2, f3);
	}

	void GLESShader::setUniform1i(const std::string& name, int value)
	{
		glUniform1i(getUniformLocation(name), value);
	}

	void GLESShader::setMatrix4f(const std::string& name, const glm::mat4& mvp)
	{
		glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE, &mvp[0][0]);
	}

	void GLESShader::setVec3f(const std::string& name, const glm::vec3& vec3)
	{
		glUniform3fv(getUniformLocation(name), 1, &vec3.x);
	}
}
