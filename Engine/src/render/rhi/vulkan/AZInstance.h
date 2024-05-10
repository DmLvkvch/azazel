#pragma once

#include "vk_headers.h"
#include <vector>
#include <set>
#include <optional>

namespace Azazel
{
    class AZInstance
    {
    public:
        AZInstance();

        ~AZInstance()
        {
            
        }

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