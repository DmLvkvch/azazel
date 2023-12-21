#pragma once

#include <vulkan/vulkan.hpp>
#include <set>
#include <optional>

namespace Azazel
{

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

    };
}