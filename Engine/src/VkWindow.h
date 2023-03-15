#pragma once

#include "Window.h"
#include <vulkan/vulkan.h>

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
        void destroyGLFW();
        void destroyImgui();
        void createInstance();

		void createDebugCallback();
		void createWindowSurface();
		void findPhysicalDevice();
		void checkSwapChainSupport();
		void findQueueFamilies();
		void createLogicalDevice();
		void createSemaphores();
		void createCommandPool();
        
        GLFWwindow* initGLFW(int width, int height, const std::string& title);
        void initImgui(GLFWwindow* window, int width, int height);
    private:
        GLFWwindow* window;
        int width;
        int height;
        std::string title;
        VkInstance instance;

        struct WindowData
        {
            EventCallbackFn eventCallback;
        };

        WindowData windowData;
    };
}