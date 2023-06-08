#include "Window.h"

#ifdef AZAZEL_GL
#include "GLWindow.h"
#else
#include "VkWindow.h"
#endif

namespace Azazel
{

    Window* Window::window = nullptr;

    Window* Window::create(const WindowProperties& props)
    {
        if (!Window::window)
        {
            #ifdef AZAZEL_GL
            Window::window = new GLWindow(props);
            #else
            Window::window = new VkWindow(props);
            #endif
        }
        return Window::window;
    }
}