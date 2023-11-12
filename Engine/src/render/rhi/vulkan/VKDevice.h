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
        {
            physicalDevice = createVkPhysicalDevice(instance);
        }

        VkPhysicalDevice createVkPhysicalDevice(VkInstance instance)
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
                if (isDeviceSuitable(device))
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

        bool isDeviceSuitable(VkPhysicalDevice device)
        {
            QueueFamilyIndices indices = findQueueFamilies(device);

            bool extensionsSupported = checkDeviceExtensionSupport(device);

            return indices.isComplete() && extensionsSupported;
        }

        bool checkDeviceExtensionSupport(VkPhysicalDevice physicalDevice)
        {
            uint32_t extensionCount;
            vkEnumerateDeviceExtensionProperties(physicalDevice, nullptr, &extensionCount, nullptr);

            std::vector<VkExtensionProperties> availableExtensions(extensionCount);
            vkEnumerateDeviceExtensionProperties(physicalDevice, nullptr, &extensionCount, availableExtensions.data());

           // std::set<std::string> requiredExtensions(deviceExtensions.begin(), deviceExtensions.end());
            std::set<std::string> requiredExtensions;

            for (const auto& extension : availableExtensions)
            {
                requiredExtensions.erase(extension.extensionName);
            }

            return requiredExtensions.empty();
        }

        QueueFamilyIndices findQueueFamilies(VkPhysicalDevice physicalDevice)
        {

            QueueFamilyIndices indices{};
            uint32_t queueFamilyCount = 0;
            vkGetPhysicalDeviceQueueFamilyProperties(physicalDevice, &queueFamilyCount, nullptr);

            std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
            vkGetPhysicalDeviceQueueFamilyProperties(physicalDevice, &queueFamilyCount, queueFamilies.data());

            for (int i = 0; i < queueFamilies.size() || !indices.isComplete(); i++)
            {
                VkBool32 presentSupport = false;
               // vkGetPhysicalDeviceSurfaceSupportKHR(physicalDevice, i, surface, &presentSupport);

                if (presentSupport)
                {
                    indices.presentFamily = i;
                }

                const auto& queueFamily = queueFamilies[i];
                if (queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT)
                {
                    indices.graphicsFamily = i;
                }
            }

            return indices;
        }

    private:
        VkPhysicalDevice physicalDevice;
    };

    class Device
    {
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