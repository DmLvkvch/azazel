#pragma once

#include "Window.h"

struct GLFWwindow;

namespace Azazel
{
    class WindowsWindow : public Window
    {
    public:
        WindowsWindow(const WindowProps& props);
        virtual ~WindowsWindow();
        void shutDown();
        void onUpdate(float delta) override;
        unsigned int getWidth() const override;
        unsigned int getHeight() const override;
        virtual void setEventCallback(const EventCallbackFn& callback) override;
        virtual void setVSync(bool enable) override;
        virtual bool isVSync() const override;
        virtual void* getNativeWindow() override;
    private:
        GLFWwindow* window;
        int width;
        int height;
        std::string title;

        struct WindowData
        {
            EventCallbackFn eventCallback;
        };

        WindowData windowData;
    };
}