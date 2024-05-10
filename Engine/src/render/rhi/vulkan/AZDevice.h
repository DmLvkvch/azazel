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
        PhysicalDevice(vk::Instance& instance, vk::SurfaceKHR& surface);

        ~PhysicalDevice();

        vk::PhysicalDevice createPhysicalDevice(vk::Instance& instance, vk::SurfaceKHR& surface);

        bool isDeviceSuitable(vk::PhysicalDevice& device, vk::SurfaceKHR& surface, std::vector<const char*>& deviceExtensions);

        bool checkDeviceExtensionSupport(vk::PhysicalDevice& physicalDevice, std::vector<const char*>& deviceExtensions);

        std::vector<vk::QueueFamilyProperties> findQueueFamilies(vk::PhysicalDevice& physicalDevice);

        std::optional<uint32_t> findPresentQueue(vk::PhysicalDevice& physicalDevice, vk::SurfaceKHR& surface);

        uint32_t findMemoryType(uint32_t typeFilter, vk::MemoryPropertyFlags properties) const;

        const vk::PhysicalDeviceProperties& getPhysicalDeviceProperties() const
        {
            return properties;
        }

        const vk::PhysicalDeviceFeatures& getPhysicalDeviceFeatures() const
        {
            return features;
        }

        vk::PhysicalDevice get() const
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

        vk::PhysicalDevice physicalDevice;
        QueueFamilyIndices indices;
        vk::PhysicalDeviceMemoryProperties memoryProperties;
        vk::PhysicalDeviceProperties properties;
        vk::PhysicalDeviceFeatures features;
    };

    class VulkanDevice
    {
    public:
        VulkanDevice(AZInstance& context, PhysicalDevice& physicalDevice);
        ~VulkanDevice();

        VkDevice createDevice(AZInstance& context, PhysicalDevice& physicalDevice);
        void destroy();

        vk::MemoryRequirements getMemoryRequirements(vk::Buffer buffer) const;
    
        AZQueue graphicsQueue;
        AZQueue presentQueue;
        vk::Device device;
    };
}
