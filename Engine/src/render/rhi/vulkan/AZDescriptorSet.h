#pragma once

#include "vk_headers.h"

namespace Azazel
{

    class VulkanDevice;

    class AZDescriptorPool
    {
    public:
        AZDescriptorPool()
        {

        }

        AZDescriptorPool(VulkanDevice& device);

        ~AZDescriptorPool()
        {

        }

        VkDescriptorPool descriptorPool;
    };

    class DescriptorSetLayout
    {
    public:
        DescriptorSetLayout()
        {
        }

        ~DescriptorSetLayout()
        {
            
        }
    
        VkDescriptorSetLayoutBinding descriptorSetLayout;
    };

    class DescriptorSet
    {

    };
}