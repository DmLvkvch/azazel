#pragma once

#include "Window.h"

namespace Azazel
{
    class WindowsWindow : public Window
    {
    public:
        WindowsWindow(const WindowProps& props);
        virttual ~WindowsWindow();

        void onUpdate() override;
        unsigned int getWidth() const override
        {
            return 0;
        }

        unsigned int getHeight() const override
        {
            return 0;
        }

        void setEventCallback(const EventCallbackFn& callback) override
        {
        }
    };
}