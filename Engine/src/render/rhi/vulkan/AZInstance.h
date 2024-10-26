#pragma once

#include <vulkan/vulkan.hpp>     // for DispatchLoaderDynamic, DebugUtilsMes...
#include <vulkan/vulkan_core.h>  // for VK_KHR_SWAPCHAIN_EXTENSION_NAME
#include <optional>
#include <set>
#include <vector>                // for vector

#include "vk_headers.h"

namespace Azazel
{
    class AZInstance
    {
    public:
        AZInstance();
        ~AZInstance();

        vk::Instance createInstance();
        void destroy();
        bool checkValidationLayerSupport(std::vector<const char*> & validationLayers);
        vk::ApplicationInfo createVkApplicationInfo(const char* applicationName, const char* engineName);
        vk::InstanceCreateInfo createVkInstanceCreateInfo(vk::ApplicationInfo* appInfo,
                                                        std::vector<const char*>& extensions, 
                                                        std::vector<const char*>& validationLayers);
        std::vector<const char*> getRequiredExtensions();
        vk::DebugUtilsMessengerEXT setupDebugMessenger(vk::Instance& instance);

        vk::Instance instance;
        vk::DebugUtilsMessengerEXT debugMessenger;
        vk::DispatchLoaderDynamic dynamicLoader {};

        std::vector<const char*> validationLayers =
        {
            "VK_LAYER_KHRONOS_validation"
        };

        std::vector<const char*> deviceExtensions =
        {
            VK_KHR_SWAPCHAIN_EXTENSION_NAME,
            #ifndef _WIN32
            "VK_KHR_portability_subset"
            #endif
        };
    };
}