#include "VulkanContext.h"
#include <iostream>
#include <exception>

namespace Azazel
{
    bool VulkanContext::checkValidationLayerSupport(std::vector<const char*> validationLayers)
    {
        uint32_t layerCount;
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

    VkApplicationInfo VulkanContext::createVkApplicationInfo()
    {
        if (!checkValidationLayerSupport(validationLayers)) 
        {
            throw std::runtime_error("validation layers requested, but not available!");
        }

        VkApplicationInfo appInfo {};
        appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
        appInfo.pApplicationName = "Hello Triangle";
        appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
        appInfo.pEngineName = "No Engine";
        appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
        appInfo.apiVersion = VK_API_VERSION_1_0;
        return appInfo;
    }

    VkInstanceCreateInfo VulkanContext::createVkInstanceCreateInfo(VkApplicationInfo& appInfo)
    {
        VkInstanceCreateInfo createInfo{};
        createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
        createInfo.pApplicationInfo = &appInfo;
        createInfo.flags = VK_INSTANCE_CREATE_ENUMERATE_PORTABILITY_BIT_KHR;

        createInfo.enabledExtensionCount = static_cast<uint32_t>(extensions.size());
        createInfo.ppEnabledExtensionNames = extensions.data();

        createInfo.enabledLayerCount = static_cast<uint32_t>(validationLayers.size());
        createInfo.ppEnabledLayerNames = validationLayers.data();
            
        return createInfo;
    }
    
    VkInstance VulkanContext::createInstance()
    {
        if (!checkValidationLayerSupport(validationLayers)) 
        {
            throw std::runtime_error("validation layers requested, but not available!");
        }

        VkApplicationInfo appInfo = createVkApplicationInfo();

        VkInstanceCreateInfo createInfo = createVkInstanceCreateInfo(appInfo);

        VkInstance instance;
        if (vkCreateInstance(&createInfo, nullptr, &instance) != VK_SUCCESS)
        {
            throw std::runtime_error("failed to create instance!");
        }
        return instance;
    }

    static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(
            VkDebugReportFlagsEXT         flags,
            VkDebugReportObjectTypeEXT    objectType,
            uint64_t                      object,
            size_t                        location,
            int32_t                       messageCode,
            const char*                   pLayerPrefix,
            const char*                   pMessage,
            void*                         pUserData)
    {
        std::cout << "(";
        if((flags & VkDebugReportFlagBitsEXT::VK_DEBUG_REPORT_INFORMATION_BIT_EXT) != 0) 
        {
            std::cout << "INFO";
        }
        if((flags & VkDebugReportFlagBitsEXT::VK_DEBUG_REPORT_WARNING_BIT_EXT) != 0) 
        {
            std::cout << "WARNING";
        }
        if((flags & VkDebugReportFlagBitsEXT::VK_DEBUG_REPORT_PERFORMANCE_WARNING_BIT_EXT) != 0)
        {
            std::cout << "PERFORMANCE";
        }
        if((flags & VkDebugReportFlagBitsEXT::VK_DEBUG_REPORT_DEBUG_BIT_EXT) != 0)
        {
            std::cout << "DEBUG";
        }
        if((flags & VkDebugReportFlagBitsEXT::VK_DEBUG_REPORT_ERROR_BIT_EXT) != 0)
        {
            std::cout << "ERROR";
        }
        std::cout << ") ";
        std::cout << "{" << pLayerPrefix << "} " << pMessage << std::endl;
        return VK_FALSE;
    }

    void VulkanContext::setupDebugInitCallback(VkInstance instance)
    {
        auto vkCreateDebugReportCallbackEXT = (PFN_vkCreateDebugReportCallbackEXT) vkGetInstanceProcAddr(instance,"vkCreateDebugReportCallbackEXT");

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
        if(vkCreateDebugReportCallbackEXT(instance, &vk_debugReportCallbackCreateInfoEXT, nullptr, &vk_debugReportCallbackEXT) != VkResult::VK_SUCCESS)
        {
            throw std::runtime_error("failed to create debug callback");
        }
    }

    VkPhysicalDevice VulkanContext::createVkPhysicalDevice(VkInstance vkInstance)
    {
        VkPhysicalDevice vkPhysicalDevice;
        {
            uint32_t vkPhysicalDevicesCount;
            if(vkEnumeratePhysicalDevices(vkInstance, &vkPhysicalDevicesCount, nullptr) != VkResult::VK_SUCCESS)
            {
              throw std::runtime_error("failed to get physical devices count");
            }
            std::vector<VkPhysicalDevice> vkPhysicalDevices(vkPhysicalDevicesCount);
            if(vkEnumeratePhysicalDevices(vkInstance, &vkPhysicalDevicesCount, vkPhysicalDevices.data()) != VkResult::VK_SUCCESS)
            {
              throw std::runtime_error("failed to get physical devices");
            }
            if(vkPhysicalDevices.empty())
            {
              throw std::runtime_error("no physical devices");
            }
            vkPhysicalDevice = vkPhysicalDevices[0];
        }
        return vkPhysicalDevice;
    }

    std::vector<VkQueueFamilyProperties> VulkanContext::getVkPhysicalDeviceQueueFamilyProperties(VkPhysicalDevice vkPhysicalDevice)
    {
        std::vector<VkQueueFamilyProperties> vkPhysicalDeviceQueueFamilyProperties;
        {
            uint32_t vkPhysicalDeviceQueueFamilyPropertiesCount;
            vkGetPhysicalDeviceQueueFamilyProperties(vkPhysicalDevice, &vkPhysicalDeviceQueueFamilyPropertiesCount, nullptr);

            vkPhysicalDeviceQueueFamilyProperties.resize(vkPhysicalDeviceQueueFamilyPropertiesCount);
            vkGetPhysicalDeviceQueueFamilyProperties(vkPhysicalDevice, &vkPhysicalDeviceQueueFamilyPropertiesCount, vkPhysicalDeviceQueueFamilyProperties.data());
        }
        return vkPhysicalDeviceQueueFamilyProperties;
    }
    
    VkDevice VulkanContext::createLogicalDevice(VkPhysicalDevice physicalDevice)
    {
        VkDevice vkDevice;

        VkPhysicalDeviceFeatures vkPhysicalDeviceFeatures {};

        std::vector<VkDeviceQueueCreateInfo> vkDeviceQueueCreateInfos(1);
        std::vector<std::vector<float>> vkDeviceQueuesPriorities(vkDeviceQueueCreateInfos.size(), std::vector<float>(1, 0.0f));
        {
            for(size_t i = 0; i < vkDeviceQueueCreateInfos.size(); ++i)
            {
                auto &vkDeviceQueueCreateInfo = vkDeviceQueueCreateInfos[i];
                auto &vkDeviceQueuePriorities = vkDeviceQueuesPriorities[i];
                vkDeviceQueueCreateInfo.sType = VkStructureType::VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
                vkDeviceQueueCreateInfo.pNext = nullptr;
                vkDeviceQueueCreateInfo.flags = 0;
                vkDeviceQueueCreateInfo.queueFamilyIndex = i;
                vkDeviceQueueCreateInfo.queueCount = vkDeviceQueuePriorities.size();
                vkDeviceQueueCreateInfo.pQueuePriorities = vkDeviceQueuePriorities.data();
            }
        }
        std::vector<const char*> validationLayers;// = getValidationLayers();

        std::vector<const char*> deviceExtensions;// = getDeviceExtenstions();

        VkDeviceCreateInfo vkDeviceCreateInfo;
        {
            vkDeviceCreateInfo.sType = VkStructureType::VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
            vkDeviceCreateInfo.pNext = nullptr;
            vkDeviceCreateInfo.flags = 0;
            vkDeviceCreateInfo.queueCreateInfoCount = vkDeviceQueueCreateInfos.size();
            vkDeviceCreateInfo.pQueueCreateInfos = vkDeviceQueueCreateInfos.data();

            vkDeviceCreateInfo.enabledLayerCount = validationLayers.size();
            vkDeviceCreateInfo.ppEnabledLayerNames = validationLayers.data();

            vkDeviceCreateInfo.enabledExtensionCount = deviceExtensions.size();
            vkDeviceCreateInfo.ppEnabledExtensionNames = deviceExtensions.data();
            vkDeviceCreateInfo.pEnabledFeatures = &vkPhysicalDeviceFeatures;
        };

        if(vkCreateDevice(vkPhysicalDevice, &vkDeviceCreateInfo, nullptr, &vkDevice) != VkResult::VK_SUCCESS)
        {
            throw std::runtime_error("failed to create device");
        }

        return vkDevice;
    }
}