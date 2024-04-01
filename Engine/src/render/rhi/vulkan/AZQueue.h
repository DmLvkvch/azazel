#pragma once

#include "vk_headers.h"

namespace Azazel
{
    class AZQueue
    {
    public:
        AZQueue()
        {

        }

        AZQueue(VkDevice device, uint32_t queueFamilyIndex);

        ~AZQueue()
        {

        }

        VkQueue createQueue(VkDevice device, uint32_t queueFamilyIndex);

        void submit(uint32_t submitCount, const VkSubmitInfo* submitInfo, VkFence fence) const
        {
            vkQueueSubmit(queue, submitCount, submitInfo, fence);
        }

        void submit(std::vector<VkSubmitInfo> & submitInfo, VkFence fence) const
        {
            vkQueueSubmit(queue, submitInfo.size(), submitInfo.data(), fence);
        }

        VkQueue get()
        {
            return queue;
        }

        VkQueue queue;
        VkQueueFlags flags;
        uint32_t queueFamilyIndex;
        uint32_t queueIndex;
    };

    class PresentQueue
    {
    public:
        PresentQueue()
        {

        };

        PresentQueue(VkDevice device, uint32_t queueFamilyIndex)
        {
            presentQueue = AZQueue(device, queueFamilyIndex);
        }

        ~PresentQueue()
        {

        }

        void present()
        {
            
        }

        AZQueue presentQueue;
    };
}