#include "VKShader.h"

#include "vk_headers.h"
#include <iostream>

namespace Azazel
{
	VKShader::VKShader(const std::string& vertexShader, const std::string& fragmentShader)
	: Shader(vertexShader, fragmentShader)
	{
		
	}

	VKShader::~VKShader()
	{
		glDeleteProgram(rendererID);
	}

	int VKShader::getShaderType(const ShaderType& shaderType) const
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

	unsigned int VKShader::compile(const std::string& programCode, const ShaderType& shaderType)
	{
		return 0;
	}

	void VKShader::bind() const
	{
	}

	void VKShader::unbind() const
	{
	}

	Shader* VKShader::setFloat(const std::string& name, float value)
	{
		return this;
	}

	Shader* VKShader::setVec4f(const std::string& name, const glm::vec4& vec4)
	{
		return this;
	}

	Shader* VKShader::setInt(const std::string& name, int value)
	{
		return this;
	}

    Shader* VKShader::setTexture(const std::string& name, const Texture& texture, int slot)
	{
		return this;
	}

	Shader* VKShader::setMatrix4f(const std::string& name, const glm::mat4& mvp)
	{
        return this;
	}

	Shader* VKShader::setVec3f(const std::string& name, const glm::vec3& vec3)
	{
        return this;
	}

	Shader* VKShader::setVec2f(const std::string& name, const glm::vec2& vec2)
	{
        return this;
	}
}
