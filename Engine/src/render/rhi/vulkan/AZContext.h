#pragma once

#include "vk_headers.h"
#include <GLFW/glfw3.h>
#include <vector>
#include "render/rhi/vulkan/AZCommandBuffer.h"
#include "render/rhi/vulkan/AZInstance.h"
#include "render/rhi/vulkan/AZSurface.h"
#include "render/rhi/vulkan/AZDevice.h"
#include "render/rhi/vulkan/AZSwapChain.h"
#include "render/rhi/vulkan/AZRenderPass.h"
#include "render/rhi/vulkan/AZFramebuffer.h"
#include "render/rhi/vulkan/AZDescriptorSet.h"

namespace Azazel
{
    class AZContext;
    class Window;
    void setVulkanContext(AZContext& context);
    AZContext& getVulkanContext();

    class AZContext
    {
    public:
        std::unique_ptr<AZInstance> instance;
        std::unique_ptr<PhysicalDevice> physicalDevice;
        std::unique_ptr<VulkanDevice> device;
        std::unique_ptr<AZDescriptorPool> descriptorPool;
        std::unique_ptr<AZSurface> surface;
        std::unique_ptr<AZSwapChain> swapchain;
        std::unique_ptr<AZRenderPass> renderPass;
        std::vector<AZFramebuffer> swapChainFramebuffers;

        void init(Window& window);
        void destroy();
    };

    class ImGuiContext
    {
        void init(GLFWwindow* window);
        void destroy();
    };
}