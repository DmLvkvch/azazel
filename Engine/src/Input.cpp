#include "Input.h"

#include "Application.h"
#include "Window.h"
#include <GLFW/glfw3.h>

namespace Azazel
{
	Input* Input::input = nullptr;

	Input::Input()
	{

	}

	Input::~Input()
	{

	}

	bool Input::isKeyPressed(int keycode)
	{
		auto window = static_cast<GLFWwindow*>(Application::getApplication()->getWindow()->getNativeWindow());
		int state = glfwGetKey(window, keycode);
		return state == GLFW_PRESS || state == GLFW_REPEAT;
	}

	bool Input::isMouseButtonPressed(int button)
	{
		auto window = static_cast<GLFWwindow*>(Application::getApplication()->getWindow()->getNativeWindow());
		int state = glfwGetMouseButton(window, button);
		return state == GLFW_PRESS;
	}

	std::pair<float, float> Input::getMousePosition()
	{
		auto window = static_cast<GLFWwindow*>(Application::getApplication()->getWindow()->getNativeWindow());
		
		double x, y;
		glfwGetCursorPos(window, &x, &y);
		return { (float)x, (float)y };
	}

	Input* Input::getInput()
	{
		if (!Input::input)
		{
			Input::input = new Input();
		}
		return Input::input;
	}
}