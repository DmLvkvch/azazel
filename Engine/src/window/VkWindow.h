#pragma once

#include "Window.h"
#include <vulkan/vulkan.hpp>

#include <vector>
#include <optional>

struct GLFWwindow;

namespace Azazel
{
    class VkWindow : public Window
    {
    public:
        VkWindow(const WindowProperties& props);
        virtual ~VkWindow();
        void shutDown();
        void onUpdate(float delta) override;
        unsigned int getWidth() const override;
        unsigned int getHeight() const override;
        virtual void setEventCallback(const EventCallbackFn& callback) override;
        virtual void setVSync(bool enable) override;
        virtual bool isVSync() const override;
        virtual void* getNativeWindow() override;
    private:
        GLFWwindow* initGLFW(int width, int height, const std::string& title);
        void initGLFWCallbacks(GLFWwindow*);

        void destroyGLFW();

    private:
        std::string title;

        GLFWwindow* window;
        int width;
        int height;

        struct WindowData
        {
            EventCallbackFn eventCallback;
        };

        WindowData windowData;
    };
}
