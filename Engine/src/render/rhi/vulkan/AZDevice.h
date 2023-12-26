#pragma once

#include "VKContext.h"
#include "AZQueue.h"
#include <set>
#include <optional>

namespace Azazel
{

    class PhysicalDevice
    {
    public:
        PhysicalDevice()
        {
        }

        PhysicalDevice(VkInstance instance, VkSurfaceKHR surface)
        {
            physicalDevice = createPhysicalDevice(instance, surface);
            vkGetPhysicalDeviceMemoryProperties(physicalDevice, &memoryProperties);
        }

        ~PhysicalDevice()
        {

        }

        VkPhysicalDevice createPhysicalDevice(VkInstance instance, VkSurfaceKHR surface);

        bool isDeviceSuitable(VkPhysicalDevice& device, VkSurfaceKHR surface, std::vector<const char*>& deviceExtensions);

        bool checkDeviceExtensionSupport(VkPhysicalDevice& physicalDevice, std::vector<const char*>& deviceExtensions);

        std::vector<VkQueueFamilyProperties> findQueueFamilies(VkPhysicalDevice& physicalDevice);

        std::optional<uint32_t> findPresentQueue(VkPhysicalDevice & physicalDevice, VkSurfaceKHR surface);

        uint32_t findMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties)
        {
            for (uint32_t i = 0; i < memoryProperties.memoryTypeCount; i++) {
                if ((typeFilter & (1 << i)) && (memoryProperties.memoryTypes[i].propertyFlags & properties) == properties) 
                {
                    return i;
                }
            }

            throw std::runtime_error("failed to find suitable memory type!");
        }

        std::vector<const char*> deviceExtensions =
        {
            VK_KHR_SWAPCHAIN_EXTENSION_NAME,
            #ifndef _WIN32
            "VK_KHR_portability_subset"
            #endif
        };

        VkPhysicalDevice physicalDevice;
        QueueFamilyIndices indices;
        VkPhysicalDeviceMemoryProperties memoryProperties;
    };

    class VulkanDevice
    {
    public:
        VulkanDevice()
        {

        }

        VulkanDevice(VulkanContext& context, PhysicalDevice& physicalDevice);

        VkDevice createDevice(VulkanContext& context, PhysicalDevice& physicalDevice);
        void destroy();

        AZQueue graphicsQueue;
        AZQueue presentQueue;

        VkDevice device;
    };
}
