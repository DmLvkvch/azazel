#include "AZInstance.h"

#include <iostream>
#include <exception>
#include <GLFW/glfw3.h>
#include "api/logging/Log.h"

namespace Azazel
{
    VkResult CreateDebugUtilsMessengerEXT(VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDebugUtilsMessengerEXT* pDebugMessenger) 
    {
        auto func = (PFN_vkCreateDebugUtilsMessengerEXT)vkGetInstanceProcAddr(instance, "vkCreateDebugUtilsMessengerEXT");
        if (func) 
        {
            return func(instance, pCreateInfo, pAllocator, pDebugMessenger);
        }
        else 
        {
            return VK_ERROR_EXTENSION_NOT_PRESENT;
        }
    }

    void DestroyDebugUtilsMessengerEXT(VkInstance instance, VkDebugUtilsMessengerEXT debugMessenger, const VkAllocationCallbacks* pAllocator) 
    {
        auto func = (PFN_vkDestroyDebugUtilsMessengerEXT)vkGetInstanceProcAddr(instance, "vkDestroyDebugUtilsMessengerEXT");
        if (func) 
        {
            func(instance, debugMessenger, pAllocator);
        }
    }

    AZInstance::AZInstance()
    {
        instance = createInstance();
    }

    AZInstance::~AZInstance()
    {
        destroy();
    }

    vk::Instance AZInstance::createInstance() 
    {
        (void) checkValidationLayerSupport(validationLayers);

        vk::ApplicationInfo appInfo = createVkApplicationInfo("Azazel", "Azazel Engine");

        auto extensions = getRequiredExtensions();

        vk::InstanceCreateInfo createInfo = createVkInstanceCreateInfo(&appInfo, extensions, validationLayers);
        
        vk::Instance instance = vk::createInstance(createInfo);

        debugMessenger = setupDebugMessenger(instance);

        return instance;
    }

    void AZInstance::destroy()
    {
        DestroyDebugUtilsMessengerEXT(instance, debugMessenger, nullptr);
        instance.destroy();
    }

    bool AZInstance::checkValidationLayerSupport(std::vector<const char*> & validationLayers)
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

    vk::ApplicationInfo AZInstance::createVkApplicationInfo(const char* applicationName, const char* engineName)
    {
        vk::ApplicationInfo appInfo;
        appInfo.setPApplicationName(applicationName)
               .setApplicationVersion(VK_MAKE_VERSION(1, 0, 0))
               .setPEngineName(engineName)
               .setEngineVersion(VK_MAKE_VERSION(1, 0, 0))
               .setApiVersion(VK_API_VERSION_1_3);
        return appInfo;
    }

    std::vector<const char*> AZInstance::getRequiredExtensions()
    {
        uint32_t glfwExtensionCount = 0;
        const char** glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

        std::vector<const char*> extensions(glfwExtensions, glfwExtensions + glfwExtensionCount);

        extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
        extensions.push_back("VK_KHR_portability_enumeration");
        extensions.push_back("VK_KHR_get_physical_device_properties2");

        return extensions;
    }

    vk::InstanceCreateInfo AZInstance::createVkInstanceCreateInfo(vk::ApplicationInfo* appInfo,
                                                              std::vector<const char*>& extensions,   
                                                              std::vector<const char*>& validationLayers)
    {
        vk::InstanceCreateInfo instanceCreateInfo {};
        instanceCreateInfo.setPApplicationInfo(appInfo)
                          .setFlags(vk::InstanceCreateFlagBits::eEnumeratePortabilityKHR)
                          .setEnabledExtensionCount(static_cast<uint32_t>(extensions.size()))
                          .setPpEnabledExtensionNames(extensions.data())
                          .setEnabledLayerCount(static_cast<uint32_t>(validationLayers.size()))
                          .setPpEnabledLayerNames(validationLayers.data());
        return instanceCreateInfo;   
    }

    static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(
        VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity, 
        VkDebugUtilsMessageTypeFlagsEXT messageType, 
        const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData, 
        void* pUserData)
    {
        Log::getLogger().errorLog(pCallbackData->pMessage);
        return VK_FALSE;
    }

    vk::DebugUtilsMessengerEXT AZInstance::setupDebugMessenger(vk::Instance& instance) 
    {
        VkDebugUtilsMessengerCreateInfoEXT createInfo {};
        createInfo.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
        createInfo.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
        createInfo.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
        createInfo.pfnUserCallback = debugCallback;
        VkDebugUtilsMessengerEXT debugMessenger;
        CreateDebugUtilsMessengerEXT(instance, &createInfo, nullptr, &debugMessenger);
        return {debugMessenger};
    }
}