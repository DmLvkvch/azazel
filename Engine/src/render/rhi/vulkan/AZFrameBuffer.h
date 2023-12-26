#pragma once

#include "vk_headers.h"

namespace Azazel
{
    struct AZFramebufferDesc
    {
        uint32_t width;
        uint32_t height;
        VkRenderPass renderPass;
        std::vector<VkImageView> attachments;
    };

    class AZFramebuffer
    {
    public:
        AZFramebuffer() {}
        AZFramebuffer(VkDevice& device, AZFramebufferDesc& framebufferDesc);

        ~AZFramebuffer()
        {

        }

        void destroy()
        {
            //vkDestroyFramebuffer(nullptr, framebuffer, nullptr);
        }

        VkFramebuffer get()
        {
            return framebuffer;
        }

        VkFramebuffer framebuffer;
    };
}