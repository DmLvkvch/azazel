#pragma once

#include <vulkan/vulkan.hpp>
#include <set>
#include <optional>

namespace Azazel
{
struct QueueFamilyIndices
    {
        std::optional<uint32_t> presentFamily;
        std::optional<uint32_t> graphicsFamily;

        bool isComplete()
        {
            return true;
        }
    };

class PhysicalDevice
{
public:
    PhysicalDevice(VkInstance instance)
    : instance(instance)
    {
        //physicalDevice = createVkPhysicalDevice(instance);
    }

    VkPhysicalDevice pickPhysicalDevice(VkInstance instance)
    {

    }

    ~PhysicalDevice()
    {

    }

    VkPhysicalDevice physicalDevice;
    
    VkInstance instance;
};

    class Device
    {
        Device()
        {

        }

        Device(VkInstance instance, VkPhysicalDevice physicalDevice)
        {
            device = createVkDevice(physicalDevice);
        }

        VkDevice createVkDevice(VkPhysicalDevice physicalDevice)
        {
            VkDevice device = createLogicalDevice(physicalDevice);
            return device;
        }

        VkDevice createLogicalDevice(VkPhysicalDevice physicalDevice)
        {
            VkDevice device;
            QueueFamilyIndices indices;// = findQueueFamilies(physicalDevice);

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

            VkPhysicalDeviceFeatures deviceFeatures{};

            VkDeviceCreateInfo createInfo{};
            {
                createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
                createInfo.queueCreateInfoCount = static_cast<uint32_t>(queueCreateInfos.size());
                createInfo.pQueueCreateInfos = queueCreateInfos.data();
                createInfo.pEnabledFeatures = &deviceFeatures;
                createInfo.enabledExtensionCount = 0;
               // createInfo.enabledLayerCount = static_cast<uint32_t>(validationLayers.size());
               // createInfo.ppEnabledLayerNames = validationLayers.data();
               // createInfo.enabledExtensionCount = static_cast<uint32_t>(deviceExtensions.size());
               // createInfo.ppEnabledExtensionNames = deviceExtensions.data();
            }

            if (vkCreateDevice(physicalDevice, &createInfo, nullptr, &device) != VK_SUCCESS)
            {
                throw std::runtime_error("failed to create logical device!");
            }

          //  vkGetDeviceQueue(device, indices.graphicsFamily.value(), 0, &graphicsQueue);
          //  vkGetDeviceQueue(device, indices.presentFamily.value(), 0, &presentQueue);
            return device;
        }

        VkDevice device;
    };
}