#pragma once

#include "vk_headers.h"
#include <vector>
#include <set>
#include <optional>

namespace Azazel
{

    class VulkanContext
    {
    public:
        VulkanContext()
        {
            instance = createInstance();
        }

        VkInstance createInstance();

        void destroy();

        bool checkValidationLayerSupport(std::vector<const char*> & validationLayers);
        VkApplicationInfo createVkApplicationInfo(const char* applicationName, const char* engineName);
        VkInstanceCreateInfo createVkInstanceCreateInfo(VkApplicationInfo* appInfo,
                                                        std::vector<const char*>& extensions, 
                                                        std::vector<const char*>& validationLayers);

        std::vector<const char*> getRequiredExtensions();
        void setupDebugMessenger(VkInstance instance);

        VkInstance instance;

        VkDebugUtilsMessengerEXT debugMessenger;

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