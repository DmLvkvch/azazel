#pragma once

#include <vulkan/vulkan.hpp>
#include <GLFW/glfw3.h>

namespace Azazel
{
    inline void defaultVulkanContextCallback(const std::string&) { }

    class Window;

    class VulkanSurface
    {
    public:
        bool ñheckVulkanPresentationSupport(const VkInstance& instance, const VkPhysicalDevice& physicalDevice, uint32_t familyQueueIndex)
        {
            return glfwGetPhysicalDevicePresentationSupport(instance, physicalDevice, familyQueueIndex) == GLFW_TRUE;
        }

        VkSurfaceKHR createSurface(VkInstance& instance, GLFWwindow* window)
        {
            glfwCreateWindowSurface(instance, window, nullptr, &surface);
            return surface;
        }

        VkSurfaceKHR surface;
    };

    class VulkanPhysicalDevice
    {

    };

    class VulkanDevice
    {

    };

    class VulkanContext
    {
        VulkanContext(Window* window);

    private:
        VkInstance createInstance();
        bool checkValidationLayerSupport(std::vector<const char*> validationLayers);
        VkApplicationInfo createVkApplicationInfo();
        VkInstanceCreateInfo createVkInstanceCreateInfo(VkApplicationInfo& appInfo);
        VkPhysicalDevice createVkPhysicalDevice(VkInstance vkInstance);
        void setupDebugInitCallback(VkInstance vkInstance);

        std::vector<VkQueueFamilyProperties> getVkPhysicalDeviceQueueFamilyProperties(VkPhysicalDevice vkPhysicalDevice);
        VkDevice createLogicalDevice(VkPhysicalDevice physicalDevice);
        std::vector<VkDeviceQueueCreateInfo> createVkDeviceQueueCreateInfo();
    private:
        std::vector<const char*> validationLayers;
        std::vector<const char*> extensions;
        VkInstance vkInstance;
        VkPhysicalDevice vkPhysicalDevice;
        VkDevice vkDevice;

    };
}