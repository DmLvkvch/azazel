#include "Window.h"
#define _CRTDBG_MAP_ALLOC

#include "WindowsWindow.h"

namespace Azazel
{

    Window* Window::window = nullptr;

    Window* Window::create(const WindowProperties& props)
    {
        if (!Window::window)
        {
            Window::window = new WindowsWindow(props);
        }
        return Window::window;
    }
}