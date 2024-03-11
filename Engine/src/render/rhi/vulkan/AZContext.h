#pragma once

#include "vk_headers.h"

namespace Azazel
{
    class AZContext
    {
    public:
        VkInstance instance;
        VkPhysicalDevice physicalDevice;
        VkDevice device;
    };

    void setVulkanContext(AZContext& context);
    AZContext& getVulkanContext();
}