#pragma once

#include "vk_headers.h"

namespace Azazel
{
    class AZDescriptorPool
    {
    public:
        AZDescriptorPool()
        {

        }

        AZDescriptorPool(VkDevice device, uint32_t descriptorCount)
        {
            VkDescriptorPoolSize poolSize {};
            poolSize.type = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
            poolSize.descriptorCount = descriptorCount;

            VkDescriptorPoolCreateInfo poolInfo {};
            poolInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
            poolInfo.poolSizeCount = 1;
            poolInfo.pPoolSizes = &poolSize;
            poolInfo.maxSets = descriptorCount;
            vkCreateDescriptorPool(device, &poolInfo, nullptr, &descriptorPool);
        }

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
            VkDescriptorSetLayoutBinding layoutBinding;
            layoutBinding.binding = 0;
            layoutBinding.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
            layoutBinding.descriptorCount = 1;
            layoutBinding.pImmutableSamplers = nullptr;
            layoutBinding.stageFlags = VK_SHADER_STAGE_ALL_GRAPHICS;

            VkDescriptorSetLayoutCreateInfo layoutInfo {};
            layoutInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
            layoutInfo.bindingCount = 1;
            layoutInfo.pBindings = &layoutBinding;

            //vkCreateDescriptorSetLayout(device->device, &layoutInfo, nullptr, &descriptorSetLayout);
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