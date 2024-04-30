#include "AZDevice.h"

namespace Azazel
{

    PhysicalDevice::PhysicalDevice(VkInstance instance, VkSurfaceKHR surface)
    {
        physicalDevice = createPhysicalDevice(instance, surface);
        vkGetPhysicalDeviceMemoryProperties(physicalDevice, &memoryProperties);
        vkGetPhysicalDeviceProperties(physicalDevice, &properties);
        vkGetPhysicalDeviceFeatures(physicalDevice, &features);
    }

    PhysicalDevice::~PhysicalDevice()
    {
    }

    VkPhysicalDevice PhysicalDevice::createPhysicalDevice(VkInstance instance, VkSurfaceKHR surface)
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

        for (auto& device : devices)
        {
            if (isDeviceSuitable(device, surface, deviceExtensions))
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

    bool PhysicalDevice::isDeviceSuitable(VkPhysicalDevice & device, VkSurfaceKHR surface, std::vector<const char*>& deviceExtensions)
    {
        auto queueFamilies = findQueueFamilies(device);
        
        for (int i = 0; i < queueFamilies.size(); i++)
        {
            const auto& queueFamily = queueFamilies[i];

            if (queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT)
            {
                indices.graphicsFamily = i;
            }

            if (queueFamily.queueFlags & VK_QUEUE_COMPUTE_BIT)
            {
                indices.computeFamily = i;
            }
        }

        indices.presentFamily = findPresentQueue(device, surface);

        bool extensionsSupported = checkDeviceExtensionSupport(device, deviceExtensions);

        return indices.isComplete() && extensionsSupported;
    }

    bool PhysicalDevice::checkDeviceExtensionSupport(VkPhysicalDevice & physicalDevice, std::vector<const char*>& deviceExtensions)
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

    std::vector<VkQueueFamilyProperties> PhysicalDevice::findQueueFamilies(VkPhysicalDevice & physicalDevice)
    {
        QueueFamilyIndices indices{};
        uint32_t queueFamilyCount = 0;
        vkGetPhysicalDeviceQueueFamilyProperties(physicalDevice, &queueFamilyCount, nullptr);

        std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
        vkGetPhysicalDeviceQueueFamilyProperties(physicalDevice, &queueFamilyCount, queueFamilies.data());
        return queueFamilies;
    }

    std::optional<uint32_t> PhysicalDevice::findPresentQueue(VkPhysicalDevice & physicalDevice, VkSurfaceKHR surface)
    {
        QueueFamilyIndices indices{};
        uint32_t queueFamilyCount = 0;
        vkGetPhysicalDeviceQueueFamilyProperties(physicalDevice, &queueFamilyCount, nullptr);
        std::optional<uint32_t> presentFamily;
        for (int i = 0; i < queueFamilyCount; i++)
        {
            VkBool32 presentSupport = false;
            vkGetPhysicalDeviceSurfaceSupportKHR(physicalDevice, i, surface, &presentSupport);
            if (presentSupport)
            {
                presentFamily = i;
                break;
            }
        }
        return presentFamily;
    }

    uint32_t PhysicalDevice::findMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties) const
    {
        for (uint32_t i = 0; i < memoryProperties.memoryTypeCount; i++) 
        {
            if ((typeFilter & (1 << i)) && (memoryProperties.memoryTypes[i].propertyFlags & properties) == properties) 
            {
                return i;
            }
        }
        return uint32_t(-1);
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    VulkanDevice::VulkanDevice(AZInstance& context, PhysicalDevice& physicalDevice)
    {
        device = createDevice(context, physicalDevice);
        graphicsQueue = AZQueue(device, physicalDevice.getQueueFamilyIndices().graphicsFamily.value());
        presentQueue = AZQueue(device, physicalDevice.getQueueFamilyIndices().presentFamily.value());
    }

    VulkanDevice::~VulkanDevice()
    {
        destroy();
    }

    VkDevice VulkanDevice::createDevice(AZInstance& context, PhysicalDevice& physicalDevice)
    {
        VkDevice device;
        const QueueFamilyIndices& indices = physicalDevice.getQueueFamilyIndices();
        std::vector<VkDeviceQueueCreateInfo> queueCreateInfos;
        std::set<uint32_t> uniqueQueueFamilies = { indices.graphicsFamily.value(), indices.presentFamily.value() };
        float queuePriority = 1.0f;
        for (uint32_t queueFamily : uniqueQueueFamilies)
        {
            VkDeviceQueueCreateInfo queueCreateInfo{};
            queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
            queueCreateInfo.queueFamilyIndex = queueFamily;
            queueCreateInfo.queueCount = 1;
            queueCreateInfo.pQueuePriorities = &queuePriority;
            queueCreateInfos.push_back(queueCreateInfo);
        }
        VkPhysicalDeviceFeatures deviceFeatures = physicalDevice.getPhysicalDeviceFeatures();
        auto& deviceExtensions = context.deviceExtensions;
        auto& validationLayers = context.validationLayers;
        VkDeviceCreateInfo createInfo{};
        {
            createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
            createInfo.queueCreateInfoCount = static_cast<uint32_t>(queueCreateInfos.size());
            createInfo.pQueueCreateInfos = queueCreateInfos.data();
            createInfo.pEnabledFeatures = &deviceFeatures;
            createInfo.enabledExtensionCount = 0;
            createInfo.enabledLayerCount = static_cast<uint32_t>(validationLayers.size());
            createInfo.ppEnabledLayerNames = validationLayers.data();
            createInfo.enabledExtensionCount = static_cast<uint32_t>(deviceExtensions.size());
            createInfo.ppEnabledExtensionNames = deviceExtensions.data();
        }
        vkCreateDevice(physicalDevice.get(), &createInfo, nullptr, &device);
        return device;
    }

    void VulkanDevice::destroy()
    {
        vkDestroyDevice(device, nullptr);
    }

    VkMemoryRequirements VulkanDevice::getMemoryRequirements(VkBuffer buffer) const
    {
        VkMemoryRequirements memRequirements;
        vkGetBufferMemoryRequirements(device, buffer, &memRequirements);
        return memRequirements;
    }
}

