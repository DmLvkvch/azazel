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

    class PhysicalDevice
    {
    public:
        PhysicalDevice()
        {
        }

        PhysicalDevice(VkInstance instance, VkSurfaceKHR surface)
        {
            this->surface = surface;
            physicalDevice = createPhysicalDevice(instance);
        }

        ~PhysicalDevice()
        {

        }

        VkPhysicalDevice createPhysicalDevice(VkInstance instance)
        {
            VkPhysicalDevice physicalDevice = pickPhysicalDevice(instance);
            return physicalDevice;
        }

        VkPhysicalDevice pickPhysicalDevice(VkInstance instance) 
        {
            uint32_t deviceCount = 0;
            VkPhysicalDevice physicalDevice = nullptr;
            vkEnumeratePhysicalDevices(instance, &deviceCount, nullptr);

            if (!deviceCount) 
            {
                throw std::runtime_error("failed to find GPUs with Vulkan support!");
            }

            std::vector<VkPhysicalDevice> devices(deviceCount);
            vkEnumeratePhysicalDevices(instance, &deviceCount, devices.data());

            for (const auto& device : devices) 
            {
                if (isDeviceSuitable(device, deviceExtensions)) 
                {
                    physicalDevice = device;
                    break;
                }
            }

            if (!physicalDevice) 
            {
                throw std::runtime_error("failed to find a suitable GPU!");
            }
            return physicalDevice;
        }

        bool isDeviceSuitable(VkPhysicalDevice device, std::vector<const char*> & deviceExtensions) 
        {
            indices = findQueueFamilies(device);

            bool extensionsSupported = checkDeviceExtensionSupport(device, deviceExtensions);

            return indices.isComplete() && extensionsSupported;
        }

        bool checkDeviceExtensionSupport(VkPhysicalDevice physicalDevice, std::vector<const char*>& deviceExtensions)
        {
            uint32_t extensionCount;
            vkEnumerateDeviceExtensionProperties(physicalDevice, nullptr, &extensionCount, nullptr);

            std::vector<VkExtensionProperties> availableExtensions(extensionCount);
            vkEnumerateDeviceExtensionProperties(physicalDevice, nullptr, &extensionCount, availableExtensions.data());

            std::set<std::string> requiredExtensions(deviceExtensions.begin(), deviceExtensions.end());

            for (const auto& extension : availableExtensions)
            {
                requiredExtensions.erase(extension.extensionName);
            }

            return requiredExtensions.empty();
        }

        QueueFamilyIndices findQueueFamilies(VkPhysicalDevice physicalDevice)
        {
            QueueFamilyIndices indices {};
            uint32_t queueFamilyCount = 0;
            vkGetPhysicalDeviceQueueFamilyProperties(physicalDevice, &queueFamilyCount, nullptr);

            std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
            vkGetPhysicalDeviceQueueFamilyProperties(physicalDevice, &queueFamilyCount, queueFamilies.data());

            for (int i = 0; i < queueFamilies.size() || !indices.isComplete(); i++)
            {
                VkBool32 presentSupport = false;
                vkGetPhysicalDeviceSurfaceSupportKHR(physicalDevice, i, surface, &presentSupport);

                if (presentSupport) 
                {
                    indices.presentFamily = i;
                }

                const auto& queueFamily = queueFamilies[i];
                if (queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT) 
                {
                    indices.graphicsFamily = i;
                }

                if (queueFamily.queueFlags & VK_QUEUE_COMPUTE_BIT)
                {
                    indices.computeQueue = i;
                }
            }
            return indices;
        }

        std::vector<const char*> deviceExtensions =
        {
            VK_KHR_SWAPCHAIN_EXTENSION_NAME,
            #ifndef _WIN32
            "VK_KHR_portability_subset"
            #endif
        };

        VkSurfaceKHR surface;
        VkPhysicalDevice physicalDevice;
        QueueFamilyIndices indices;
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
        bool checkValidationLayerSupport(std::vector<const char*> & validationLayers);
        VkApplicationInfo createVkApplicationInfo(const char* applicationName, const char* engineName);
        VkInstanceCreateInfo createVkInstanceCreateInfo(VkApplicationInfo* appInfo,
                                                              std::vector<const char*>& extensions, 
                                                              std::vector<const char*>& validationLayers);
        std::vector<const char*> getRequiredExtensions();

        void setupDebugInitCallback(VkInstance vkInstance);

        VkInstance instance;

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
    
    class VulkanDevice
    {
    public:
        VulkanDevice()
        {

        }

        VulkanDevice(VulkanContext & context, PhysicalDevice physicalDevice)
        {
            device = createLogicalDevice(context, physicalDevice);
        }

        VkDevice createLogicalDevice(VulkanContext & context, PhysicalDevice & physicalDevice);

        VkQueue createQueue(uint32_t queueFamilyIndex);

        VkQueue graphicsQueue;
        VkQueue presentQueue;

        VkDevice device;
    };
}