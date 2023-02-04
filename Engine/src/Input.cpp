#include "Input.h"

#include "Application.h"
#include "Window.h"
#include <GLFW/glfw3.h>

namespace Azazel
{
    std::unique_ptr<Input> Input::input(new Input());

    Input* Input::getInput()
    {
        return Input::input.get();
    }

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
        return state == GLFW_PRESS;
    }

    bool Input::isMouseButtonPressed(int button)
    {
        auto window = static_cast<GLFWwindow*>(Application::getApplication()->getWindow()->getNativeWindow());
        int state = glfwGetMouseButton(window, button);
        return state == GLFW_PRESS;
    }

    bool Input::isKeyHeld(int keycode)
    {
        auto window = static_cast<GLFWwindow*>(Application::getApplication()->getWindow()->getNativeWindow());
        int state = glfwGetKey(window, keycode);
        return state == GLFW_PRESS || state == GLFW_REPEAT;
    }


    std::pair<float, float> Input::getMousePosition()
    {
        auto window = static_cast<GLFWwindow*>(Application::getApplication()->getWindow()->getNativeWindow());
        double x = 0.0;
        double y = 0.0;
        glfwGetCursorPos(window, &x, &y);
        return { (float) x, (float) y };
    }
}