#include "GLESShader.h"

#include "gl_headers.h"
#include <iostream>

namespace Azazel
{
	GLESShader::GLESShader(const std::string& vertexShader, const std::string& fragmentShader)
	: Shader(vertexShader, fragmentShader)
	{
		unsigned int vertexShaderHandle = compile(vertexShader, VERTEX);
		unsigned int fragmentShaderHandle = compile(fragmentShader, FRAGMENT);

		rendererID = glCreateProgram();

		glAttachShader(rendererID, vertexShaderHandle);
		glAttachShader(rendererID, fragmentShaderHandle);
		glLinkProgram(rendererID);
		glDeleteShader(vertexShaderHandle);
		glDeleteShader(fragmentShaderHandle);

		int success;
		glGetProgramiv(rendererID, GL_LINK_STATUS, &success);
		char infoLog[512];
		if (!success) 
		{
			glGetProgramInfoLog(rendererID, 512, NULL, infoLog);
			std::cout << "Shader program creation error!\n" << infoLog << std::endl;
		}
	}

	GLESShader::~GLESShader()
	{
		glDeleteProgram(rendererID);
	}

	int GLESShader::getShaderType(const ShaderType& shaderType) const
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

		int status;
		char infoLog[512];

		glGetShaderiv(handle, GL_COMPILE_STATUS, &status);

		if (status != GL_TRUE) {
			glGetProgramInfoLog(rendererID, 512, NULL, infoLog);
			std::cout << "Shader compile error!\n" << infoLog << std::endl<<programCode<<std::endl;
			glGetShaderInfoLog(rendererID, 512, nullptr, infoLog);
		}

		return handle;
	}

	void GLESShader::bind() const
	{
		glUseProgram(rendererID);
	}

	void GLESShader::unbind() const
	{
		glUseProgram(0);
	}

	int GLESShader::getUniformLocation(const std::string& name)
	{
		auto uniformLocation = uniformLocationMap.find(name);
		if (uniformLocation != uniformLocationMap.end())
		{
			return uniformLocation->second;
		}
		int location = glGetUniformLocation(rendererID, name.c_str());
		if (location == -1)
		{
			std::cout << "No active uniform variable with name " << name << " found" << std::endl;
		}
		else
		{
			uniformLocationMap[name] = location;
		}
		return location;
	}

	Shader* GLESShader::setFloat(const std::string& name, float value)
	{
		glUniform1f(getUniformLocation(name), value);
		return this;
	}

	Shader* GLESShader::setVec4f(const std::string& name, const glm::vec4& vec4)
	{
		glUniform4f(getUniformLocation(name), vec4.x, vec4.y, vec4.z, vec4.w);
		return this;
	}

	Shader* GLESShader::setInt(const std::string& name, int value)
	{
		glUniform1i(getUniformLocation(name), value);
		return this;
	}

    Shader* GLESShader::setTexture(const std::string& name, const Texture& texture, int slot)
	{
		texture.bind(slot);
		glUniform1i(getUniformLocation(name), slot);
		return this;
	}

    Shader* GLESShader::setTextureCube(const std::string& name, const CubeMap& cubeMap, int slot)
	{
		cubeMap.bind(slot);
		glUniform1i(getUniformLocation(name), slot);
		return this;
	}

	Shader* GLESShader::setMatrix4f(const std::string& name, const glm::mat4& mvp)
	{
		glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE, &mvp[0][0]);
        return this;
	}

	Shader* GLESShader::setVec3f(const std::string& name, const glm::vec3& vec3)
	{
		glUniform3fv(getUniformLocation(name), 1, &vec3.x);
        return this;
	}

	Shader* GLESShader::setVec2f(const std::string& name, const glm::vec2& vec2)
	{
		glUniform2fv(getUniformLocation(name), 1, &vec2.x);
        return this;
	}
}
