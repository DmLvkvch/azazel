#pragma once

#include "vk_headers.h"

namespace Azazel
{
    template <typename T> using AZArrayProxy = vk::ArrayProxy<T>;

    class AZQueue
    {
    public:
        AZQueue()
        {

        }

        AZQueue(vk::Device device, uint32_t queueFamilyIndex);

        vk::Queue createQueue(vk::Device device, uint32_t queueFamilyIndex);

        void submit(const vk::SubmitInfo* submitInfo, uint32_t submitCount, vk::Fence fence) const
        {
            AZArrayProxy<vk::SubmitInfo> submitInfos{submitCount, submitInfo};
            queue.submit(submitInfos, fence);
        }

        void submit(AZArrayProxy<vk::SubmitInfo> & submitInfo, vk::Fence fence) const
        {
            queue.submit(submitInfo, fence);
        }

        vk::Queue get()
        {
            return queue;
        }

        vk::Queue queue;
        uint32_t queueFamilyIndex;
    };

    class PresentQueue
    {
    public:
        PresentQueue()
        {

        }

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