#include "Window.h"

#include "WindowsWindow.h"

namespace Azazel
{

    std::unique_ptr<Window> Window::window = nullptr;

    Window* Window::create(const WindowProps& props)
    {
        if (!Window::window)
        {
            Window::window.reset(new WindowsWindow(props));
        }
        return Window::window.get();
    }
}