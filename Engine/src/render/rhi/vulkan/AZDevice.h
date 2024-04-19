#pragma once

#include "AZQueue.h"
#include "AZInstance.h"
#include <optional>
#include <set>
#include <array>

namespace Azazel
{
    struct QueueFamilyIndices
    {
        std::optional<uint32_t> presentFamily;
        std::optional<uint32_t> graphicsFamily;
        std::optional<uint32_t> computeFamily;

        bool isComplete() const
        {
            return presentFamily.has_value() && graphicsFamily.has_value();
        }

        std::array<uint32_t, 2> getIndices() const
        {
            return { presentFamily.value(), graphicsFamily.value() };
        }
    };

    class PhysicalDevice
    {
    public:
        PhysicalDevice(VkInstance instance, VkSurfaceKHR surface);

        ~PhysicalDevice();

        VkPhysicalDevice createPhysicalDevice(VkInstance instance, VkSurfaceKHR surface);

        bool isDeviceSuitable(VkPhysicalDevice& device, VkSurfaceKHR surface, std::vector<const char*>& deviceExtensions);

        bool checkDeviceExtensionSupport(VkPhysicalDevice& physicalDevice, std::vector<const char*>& deviceExtensions);

        std::vector<VkQueueFamilyProperties> findQueueFamilies(VkPhysicalDevice& physicalDevice);

        std::optional<uint32_t> findPresentQueue(VkPhysicalDevice & physicalDevice, VkSurfaceKHR surface);

        uint32_t findMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties) const;

        const VkPhysicalDeviceProperties& getPhysicalDeviceProperties() const
        {
            return properties;
        }

        const VkPhysicalDeviceFeatures& getPhysicalDeviceFeatures() const
        {
            return features;
        }

        VkPhysicalDevice get() const
        {
            return physicalDevice;
        }

        const QueueFamilyIndices& getQueueFamilyIndices() const
        {
            return indices;
        }

    private:
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
        VkPhysicalDeviceProperties properties;
        VkPhysicalDeviceFeatures features;
    };

    class VulkanDevice
    {
    public:
        VulkanDevice(AZInstance& context, PhysicalDevice& physicalDevice);
        ~VulkanDevice();

        VkDevice createDevice(AZInstance& context, PhysicalDevice& physicalDevice);
        void destroy();

        VkMemoryRequirements getMemoryRequirements(VkBuffer buffer) const;
    
        AZQueue graphicsQueue;
        AZQueue presentQueue;
        VkDevice device;
    };
}
