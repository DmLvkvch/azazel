#include "VKContext.h"

#include <iostream>
#include <exception>

namespace Azazel
{
    VkInstance VulkanContext::createInstance() 
    {
        if (!checkValidationLayerSupport(validationLayers)) 
        {
            throw std::runtime_error("validation layers requested, but not available!");
        }

        VkApplicationInfo appInfo = createVkApplicationInfo("Azazel", "Azazel Engine");

        auto extensions = getRequiredExtensions();

        VkInstanceCreateInfo createInfo = createVkInstanceCreateInfo(&appInfo, extensions, validationLayers);
        
        VkInstance instance;
        if (vkCreateInstance(&createInfo, nullptr, &instance) != VK_SUCCESS)
        {
            throw std::runtime_error("failed to create instance!");
        }
        return instance;
    }

    bool VulkanContext::checkValidationLayerSupport(std::vector<const char*> & validationLayers)
    {
        uint32_t layerCount = 0;
        vkEnumerateInstanceLayerProperties(&layerCount, nullptr);
        std::vector<VkLayerProperties> availableLayers(layerCount);
        vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());
        for (const char* layerName : validationLayers) 
        {
            bool layerFound = false;
            for (const auto& layerProperties : availableLayers) 
            {
                if (strcmp(layerName, layerProperties.layerName) == 0) 
                {
                    layerFound = true;
                    break;
                }
            }
            if (!layerFound)
            {
                return false;
            }
        }
        return true;
    }

    VkApplicationInfo VulkanContext::createVkApplicationInfo(const char* applicationName, const char* engineName)
    {
        VkApplicationInfo appInfo {};
        {
            appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
            appInfo.pApplicationName = applicationName;
            appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
            appInfo.pEngineName = engineName;
            appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
            appInfo.apiVersion = VK_API_VERSION_1_0;
        }
        return appInfo;
    }

    std::vector<const char*> VulkanContext::getRequiredExtensions()
    {
        uint32_t glfwExtensionCount = 0;
        const char** glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

        std::vector<const char*> extensions(glfwExtensions, glfwExtensions + glfwExtensionCount);

        extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
        extensions.push_back("VK_KHR_portability_enumeration");
        extensions.push_back("VK_KHR_get_physical_device_properties2");

        return extensions;
    }

    VkInstanceCreateInfo VulkanContext::createVkInstanceCreateInfo(VkApplicationInfo* appInfo,
                                                              std::vector<const char*>& extensions, 
                                                              std::vector<const char*>& validationLayers)
    {
        VkInstanceCreateInfo createInfo {};
        {
            createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
            createInfo.pApplicationInfo = appInfo;
            createInfo.flags = VK_INSTANCE_CREATE_ENUMERATE_PORTABILITY_BIT_KHR;
            createInfo.enabledExtensionCount = static_cast<uint32_t>(extensions.size());
            createInfo.ppEnabledExtensionNames = extensions.data();

            createInfo.enabledLayerCount = static_cast<uint32_t>(validationLayers.size());
            createInfo.ppEnabledLayerNames = validationLayers.data();
        }
        return createInfo;   
    }

    static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(
        VkDebugReportFlagsEXT         flags,
        VkDebugReportObjectTypeEXT    objectType,
        uint64_t                      object,
        size_t                        location,
        int32_t                       messageCode,
        const char* pLayerPrefix,
        const char* pMessage,
        void* pUserData)
    {
        std::cout << "(";
        if ((flags & VkDebugReportFlagBitsEXT::VK_DEBUG_REPORT_INFORMATION_BIT_EXT) != 0)
        {
            std::cout << "INFO";
        }
        if ((flags & VkDebugReportFlagBitsEXT::VK_DEBUG_REPORT_WARNING_BIT_EXT) != 0)
        {
            std::cout << "WARNING";
        }
        if ((flags & VkDebugReportFlagBitsEXT::VK_DEBUG_REPORT_PERFORMANCE_WARNING_BIT_EXT) != 0)
        {
            std::cout << "PERFORMANCE";
        }
        if ((flags & VkDebugReportFlagBitsEXT::VK_DEBUG_REPORT_DEBUG_BIT_EXT) != 0)
        {
            std::cout << "DEBUG";
        }
        if ((flags & VkDebugReportFlagBitsEXT::VK_DEBUG_REPORT_ERROR_BIT_EXT) != 0)
        {
            std::cout << "ERROR";
        }
        std::cout << ") ";
        std::cout << "{" << pLayerPrefix << "} " << pMessage << std::endl;
        return VK_FALSE;
    }

    void VulkanContext::setupDebugInitCallback(VkInstance instance)
    {
        auto vkCreateDebugReportCallbackEXT = (PFN_vkCreateDebugReportCallbackEXT)vkGetInstanceProcAddr(instance, "vkCreateDebugReportCallbackEXT");

        VkDebugReportCallbackEXT vk_debugReportCallbackEXT;

        VkDebugReportCallbackCreateInfoEXT vk_debugReportCallbackCreateInfoEXT;
        {
            vk_debugReportCallbackCreateInfoEXT.sType = VkStructureType::VK_STRUCTURE_TYPE_DEBUG_REPORT_CALLBACK_CREATE_INFO_EXT;
            vk_debugReportCallbackCreateInfoEXT.pNext = nullptr;
            vk_debugReportCallbackCreateInfoEXT.flags =
                VkDebugReportFlagBitsEXT::VK_DEBUG_REPORT_INFORMATION_BIT_EXT |
                VkDebugReportFlagBitsEXT::VK_DEBUG_REPORT_WARNING_BIT_EXT |
                VkDebugReportFlagBitsEXT::VK_DEBUG_REPORT_PERFORMANCE_WARNING_BIT_EXT |
                VkDebugReportFlagBitsEXT::VK_DEBUG_REPORT_ERROR_BIT_EXT |
                VkDebugReportFlagBitsEXT::VK_DEBUG_REPORT_DEBUG_BIT_EXT;

            vk_debugReportCallbackCreateInfoEXT.pfnCallback = debugCallback;
            vk_debugReportCallbackCreateInfoEXT.pUserData = nullptr;
        }
        if (vkCreateDebugReportCallbackEXT(instance, &vk_debugReportCallbackCreateInfoEXT, nullptr, &vk_debugReportCallbackEXT) != VkResult::VK_SUCCESS)
        {
            throw std::runtime_error("failed to create debug callback");
        }
    }


    VkDevice VulkanDevice::createLogicalDevice(VulkanContext & context, PhysicalDevice & physicalDevice)
    {
        VkDevice device;
        QueueFamilyIndices indices = physicalDevice.indices;
        std::vector<VkDeviceQueueCreateInfo> queueCreateInfos;
        std::set<uint32_t> uniqueQueueFamilies = {indices.graphicsFamily.value(), indices.presentFamily.value()};
        float queuePriority = 1.0f;
        for (uint32_t queueFamily : uniqueQueueFamilies) 
        {
            VkDeviceQueueCreateInfo queueCreateInfo {};
            queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
            queueCreateInfo.queueFamilyIndex = queueFamily;
            queueCreateInfo.queueCount = 1;
            queueCreateInfo.pQueuePriorities = &queuePriority;
            queueCreateInfos.push_back(queueCreateInfo);
        }
        VkPhysicalDeviceFeatures deviceFeatures {};
        auto deviceExtensions = context.deviceExtensions;
        auto validationLayers = context.validationLayers;
        VkDeviceCreateInfo createInfo {};
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
        if (vkCreateDevice(physicalDevice.physicalDevice, &createInfo, nullptr, &device) != VK_SUCCESS) 
        {
            throw std::runtime_error("failed to create logical device!");
        }
        vkGetDeviceQueue(device, indices.graphicsFamily.value(), 0, &graphicsQueue);
        vkGetDeviceQueue(device, indices.presentFamily.value(), 0, &presentQueue);
        return device;
    }

    VkQueue VulkanDevice::createQueue(uint32_t queueFamilyIndex)
    {
        VkQueue queue;
        vkGetDeviceQueue(device, queueFamilyIndex, 0, &queue);
        return queue;
    }

}