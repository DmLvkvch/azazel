#pragma once

#include "Window.h"
#include <vulkan/vulkan.hpp>

namespace Azazel
{
    inline void defaultVulkanContextCallback(const std::string&) { }

    struct VulkanContextCreateOptions
    {
        int vulkanApiMajorVersion = 1;
        int vulkanApiMinorVersion = 0;
        std::function<void(const std::string&)> errorCallback = defaultVulkanContextCallback;
        std::function<void(const std::string&)> infoCallback = defaultVulkanContextCallback;
        std::vector<const char*> extensions;
        std::vector<const char*> layers;
        const char* applicationName = "Azazel";
        const char* engineName = "Azazel";
    };

    enum class DeviceType
    {
        CPU = 0,
        DISCRETE_GPU,
        INTEGRATED_GPU,
        VIRTUAL_GPU,
        OTHER,
    };

    struct ContextInitializeOptions
    {
        DeviceType PreferredDeviceType = DeviceType::DISCRETE_GPU;
        std::function<void(const std::string&)> ErrorCallback = defaultVulkanContextCallback;
        std::function<void(const std::string&)> InfoCallback = defaultVulkanContextCallback;
        std::vector<const char*> deviceExtensions;
        size_t virtualFrameCount = 3;
        size_t maxStageBufferSize = 64 * 1024 * 1024;
    };

    class VulkanContext
    {
        VulkanContext(Window* window);

        private:
            VkInstance initVkInstance();
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