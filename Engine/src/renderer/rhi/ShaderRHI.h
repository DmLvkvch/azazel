#pragma once

#include <string>
#include <glm/glm.hpp>

namespace Azazel
{
	class ShaderRHI
	{
	public:
		virtual ~ShaderRHI();
		virtual void bind() = 0;
		virtual void unbind() = 0;

		virtual int getUniformLocation(const std::string& name) = 0;
		virtual void setUniform1f(const std::string& name, float value) = 0;
		virtual void setUniform1i(const std::string& name, int value) = 0;
		virtual void setUniform4f(const std::string& name, float f0, float f1, float f2, float f3) = 0;
		virtual void setMatrix4f(const std::string& name, const glm::mat4& mvp) = 0;
		virtual void setVec3f(const std::string& name, const glm::vec3& vec3) = 0;
	};
}