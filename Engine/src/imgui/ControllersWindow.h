#pragma once
#include <glm/glm.hpp>

namespace Azazel
{
	class ControllerWindow
	{
		glm::vec3 translation { 0.0f, 0.0f, 0.0f };
	public:
		void draw();
	};
}