#include "AZQueue.h"

namespace Azazel
{

    AZQueue::AZQueue(vk::Device device, uint32_t queueFamilyIndex)
    {
        this->queue = createQueue(device, queueFamilyIndex);
        this->queueFamilyIndex = queueFamilyIndex;
    }

    vk::Queue AZQueue::createQueue(vk::Device device, uint32_t queueFamilyIndex)
    {
        vk::Queue queue = device.getQueue(queueFamilyIndex, 0);
        return queue;
    }
}