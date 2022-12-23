#include "Window.h"

#include "WindowsWindow.h"

namespace Azazel
{

    Window* Window::window = nullptr;

    Window* Window::create(const WindowProps& props)
    {
        if (!Window::window)
        {
            Window::window = new WindowsWindow(props);
        }
        return Window::window;
    }
}