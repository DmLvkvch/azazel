#include "AZFramebuffer.h"

namespace Azazel
{
    AZFramebuffer::AZFramebuffer(VkDevice& device, AZFramebufferDesc& framebufferDesc)
    {
        VkFramebufferCreateInfo framebufferInfo{};
        {
            framebufferInfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
            framebufferInfo.renderPass = framebufferDesc.renderPass;
            framebufferInfo.attachmentCount = static_cast<uint32_t>(framebufferDesc.attachments.size());
            framebufferInfo.pAttachments = framebufferDesc.attachments.data();
            framebufferInfo.width = framebufferDesc.width;
            framebufferInfo.height = framebufferDesc.height;
            framebufferInfo.layers = 1;
        }
        vkCreateFramebuffer(device, &framebufferInfo, nullptr, &framebuffer);
    }
}
