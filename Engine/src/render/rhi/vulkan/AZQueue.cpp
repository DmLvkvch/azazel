#include "AZQueue.h"

namespace Azazel
{

    AZQueue::AZQueue(VkDevice device, uint32_t queueFamilyIndex)
    {
        this->queue = createQueue(device, queueFamilyIndex);
        this->queueFamilyIndex = queueFamilyIndex;
    }

    VkQueue AZQueue::createQueue(VkDevice device, uint32_t queueFamilyIndex)
    {
        VkQueue queue;
        vkGetDeviceQueue(device, queueFamilyIndex, 0, &queue);
        return queue;
    }
}