#include "AZDevice.h"

#include <set>                             // for set, __tree_const_iterator
#include <string>                          // for basic_string, string

#include "render/rhi/vulkan/AZInstance.h"  // for AZInstance
#include "render/rhi/vulkan/AZQueue.h"     // for AZQueue

namespace Azazel
{

    PhysicalDevice::PhysicalDevice(vk::Instance& instance, vk::SurfaceKHR& surface)
    {
        physicalDevice = createPhysicalDevice(instance, surface);
        memoryProperties = physicalDevice.getMemoryProperties();
        properties = physicalDevice.getProperties();
        features = physicalDevice.getFeatures();
    }

    PhysicalDevice::~PhysicalDevice()
    {
    }

    vk::PhysicalDevice PhysicalDevice::createPhysicalDevice(vk::Instance& instance, vk::SurfaceKHR& surface)
    {
        auto devices = instance.enumeratePhysicalDevices();
        for (auto& device : devices)
        {
            if (isDeviceSuitable(device, surface, deviceExtensions))
            {
                return device;
            }
        }
        return devices[0];
    }

    bool PhysicalDevice::isDeviceSuitable(vk::PhysicalDevice& device, vk::SurfaceKHR& surface, std::vector<const char*>& deviceExtensions)
    {
        auto queueFamilies = findQueueFamilies(device);
        
        for (int i = 0; i < queueFamilies.size(); i++)
        {
            const auto& queueFamily = queueFamilies[i];
            
            if (queueFamily.queueFlags & vk::QueueFlagBits::eGraphics)
            {
                indices.graphicsFamily = i;
            }

            if (queueFamily.queueFlags & vk::QueueFlagBits::eCompute)
            {
                indices.computeFamily = i;
            }
        }

        indices.presentFamily = findPresentQueue(device, surface);

        bool extensionsSupported = checkDeviceExtensionSupport(device, deviceExtensions);

        return indices.isComplete() && extensionsSupported;
    }

    bool PhysicalDevice::checkDeviceExtensionSupport(vk::PhysicalDevice& physicalDevice, std::vector<const char*>& deviceExtensions)
    {
        std::vector<vk::ExtensionProperties> availableExtensions = physicalDevice.enumerateDeviceExtensionProperties();

        std::set<std::string> requiredExtensions(deviceExtensions.begin(), deviceExtensions.end());

        for (const auto& extension : availableExtensions)
        {
            requiredExtensions.erase(extension.extensionName);
        }

        return requiredExtensions.empty();
    }

    std::vector<vk::QueueFamilyProperties> PhysicalDevice::findQueueFamilies(vk::PhysicalDevice& physicalDevice)
    {
        return physicalDevice.getQueueFamilyProperties();
    }

    std::optional<uint32_t> PhysicalDevice::findPresentQueue(vk::PhysicalDevice& physicalDevice, vk::SurfaceKHR& surface)
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

    uint32_t PhysicalDevice::findMemoryType(uint32_t typeFilter, vk::MemoryPropertyFlags properties) const
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

    VulkanDevice::VulkanDevice(const AZInstance& context, const PhysicalDevice& physicalDevice)
    : physicalDevice(physicalDevice)
    {
        device = createDevice(context, physicalDevice);
        graphicsQueue = AZQueue(device, physicalDevice.getQueueFamilyIndices().graphicsFamily.value());
        presentQueue = AZQueue(device, physicalDevice.getQueueFamilyIndices().presentFamily.value());
    }

    VulkanDevice::~VulkanDevice()
    {
        //destroy();
    }

    vk::Device VulkanDevice::createDevice(const AZInstance& context, const PhysicalDevice& physicalDevice)
    {
        vk::Device device {};
        const QueueFamilyIndices& indices = physicalDevice.getQueueFamilyIndices();
        std::vector<vk::DeviceQueueCreateInfo> queueCreateInfos;
        std::set<uint32_t> uniqueQueueFamilies = { indices.graphicsFamily.value(), indices.presentFamily.value() };
        float queuePriority = 1.0f;
        for (uint32_t queueFamily : uniqueQueueFamilies)
        {
            vk::DeviceQueueCreateInfo queueCreateInfo {};
            queueCreateInfo.setQueueFamilyIndex(queueFamily).setQueueCount(1).setPQueuePriorities(&queuePriority);
            queueCreateInfos.push_back(queueCreateInfo);
        }
        vk::PhysicalDeviceFeatures deviceFeatures = physicalDevice.getPhysicalDeviceFeatures();
        auto& deviceExtensions = context.deviceExtensions;
        auto& validationLayers = context.validationLayers;
        vk::DeviceCreateInfo createInfo {};
        createInfo.setQueueCreateInfoCount(static_cast<uint32_t>(queueCreateInfos.size()))
                  .setPQueueCreateInfos(queueCreateInfos.data()).setPEnabledFeatures(&deviceFeatures)
                  .setEnabledExtensionCount(0)
                  .setEnabledLayerCount(static_cast<uint32_t>(validationLayers.size())).setPpEnabledLayerNames(validationLayers.data())
                  .setEnabledExtensionCount(static_cast<uint32_t>(deviceExtensions.size())).setPpEnabledExtensionNames(deviceExtensions.data());
        device = physicalDevice.get().createDevice(createInfo);
        return device;
    }

    void VulkanDevice::destroy()
    {
        device.destroy();
    }

    vk::MemoryRequirements VulkanDevice::getMemoryRequirements(vk::Buffer& buffer) const
    {
        return device.getBufferMemoryRequirements(buffer);
    }
}

