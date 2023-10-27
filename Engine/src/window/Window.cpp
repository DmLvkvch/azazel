#include "Window.h"

#ifdef AZAZEL_GL
#include "GLWindow.h"
#else
#include "VkWindow.h"
#endif

namespace Azazel
{

    Window* Window::window = nullptr;

    Window* Window::create(const WindowProperties& properties)
    {
        if (!Window::window)
        {
            #ifdef AZAZEL_GL
            Window::window = new GLWindow(propropertiesps);
            #else
            Window::window = new VkWindow(properties);
            #endif
        }
        return Window::window;
    }
}