#include "VkWindow.h"

#include "events/ApplicationEvent.h"
#include "events/KeyEvent.h"
#include "events/MouseEvent.h"
#include <GLFW/glfw3.h>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_vulkan.h>
#include <iostream>

namespace Azazel
{
    static bool initialized = false;

    VkWindow::VkWindow(const WindowProperties& props)
    {

    }

    void VkWindow::initVulkan()
    {
    }

    void VkWindow::createInstance()
    {
    }

	void VkWindow::createDebugCallback()
    {
        // TODO
    }

	void VkWindow::findPhysicalDevice()
    {
       
    }

	void VkWindow::findQueueFamilies()
    {
        
    }

    void VkWindow::createLogicalDevice() {
		
        
	}

	void VkWindow::createSemaphores() {
		
	}

	void VkWindow::createCommandPool() {
		
	}
	

    bool isDeviceSutable(VkPhysicalDevice device)
    {
        return true;
    }

    VkWindow::~VkWindow()
    {
        
    }

    GLFWwindow* VkWindow::initGLFW(int width, int height, const std::string& title)
    {
        return nullptr;
    }

    void VkWindow::destroyGLFW()
    {

       
    }

    void VkWindow::initImgui(GLFWwindow* window, int width, int height)
    {

        
    }

    void VkWindow::destroyImgui()
    {
       
    }

    void VkWindow::shutDown()
    {
       
    }

    void VkWindow::onUpdate(float delta)
    {
      
    }

    unsigned int VkWindow::getWidth() const
    {
        return 0;
    }

    unsigned int VkWindow::getHeight() const
    {
        return 0;
    }

    void VkWindow::setEventCallback(const EventCallbackFn& callback)
    {
        
    }

    void VkWindow::setVSync(bool enable)
    {
        if (enable)
        {
            glfwSwapInterval(1);
        }
        else
        {
            glfwSwapInterval(0);
        }
    }

    bool VkWindow::isVSync() const
    {
        return true;
    }

    void* VkWindow::getNativeWindow()
    {
        return nullptr;
    }
}