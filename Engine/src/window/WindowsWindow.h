#pragma once

#include "Window.h"

struct GLFWwindow;

namespace Azazel
{
    class WindowsWindow : public Window
    {
    public:
        WindowsWindow(const WindowProperties& props);
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
        void destroyGLFW();
        void destroyImgui();

        GLFWwindow* initGLFW(int width, int height, const std::string& title);
        void initImgui(GLFWwindow* window, int width, int height);
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