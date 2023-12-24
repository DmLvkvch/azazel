#pragma once

#include "vk_headers.h"
#include <GLFW/glfw3.h>
#include <vector>
#include <set>
#include <optional>

namespace Azazel
{
    struct QueueFamilyIndices
    {
        std::optional<uint32_t> presentFamily;
        std::optional<uint32_t> graphicsFamily;
        std::optional<uint32_t> computeQueue;

        bool isComplete()
        {
            return presentFamily.has_value() && graphicsFamily.has_value();
        }
    };

    inline void defaultVulkanContextCallback(const std::string&) { }

    class Window;

    class VulkanSurface
    {
    public:
        bool checkVulkanPresentationSupport(const VkInstance& instance, const VkPhysicalDevice& physicalDevice, uint32_t familyQueueIndex)
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

    class VulkanContext
    {
    public:
        VulkanContext()
        {
            
        }

        VulkanContext(Window* window)
        {

        }

        VkInstance createInstance();

        void destroy();

        bool checkValidationLayerSupport(std::vector<const char*> & validationLayers);
        VkApplicationInfo createVkApplicationInfo(const char* applicationName, const char* engineName);
        VkInstanceCreateInfo createVkInstanceCreateInfo(VkApplicationInfo* appInfo,
                                                        std::vector<const char*>& extensions, 
                                                        std::vector<const char*>& validationLayers);

        std::vector<const char*> getRequiredExtensions();
        void setupDebugMessenger(VkInstance instance);

        VkInstance instance;

        VkDebugUtilsMessengerEXT debugMessenger;

        std::vector<const char*> validationLayers =
        {
            "VK_LAYER_KHRONOS_validation"
        };

        std::vector<const char*> deviceExtensions =
        {
            VK_KHR_SWAPCHAIN_EXTENSION_NAME,
            #ifndef _WIN32
            "VK_KHR_portability_subset"
            #endif
        };
    };
}