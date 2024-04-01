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

struct VmaAllocator_T;
using VmaAllocator = VmaAllocator_T*;

namespace Azazel
{
    class AZContext;
    class Window;

    void setVulkanContext(AZContext& context);
    AZContext& getVulkanContext();

    class AZContext
    {
    public:

        const AZInstance& getInstance() const 
        {
            return *instance;
        }

        const PhysicalDevice& getPhysicalDevice() const
        {
            return *physicalDevice;
        }

        const VulkanDevice& getVulkanDevice() const
        {
            return *device;
        }

        const AZQueue& getGraphicsQueue() const
        {
            return device->graphicsQueue;
        }

        const AZQueue& getPresentQueue() const
        {
            return device->presentQueue;
        }

        const AZSurface& getSurface() const
        {
            return *surface;
        }

        const AZSwapChain& getSwapChain() const
        {
            return *swapChain;
        }

        const VmaAllocator& getAllocator() const
        {
            return allocator;
        }

        const AZCommandPool& getCommandPool() const
        {
            return *commandPool;
        }

        const AZRenderPass& getRenderPass() const
        {
            return *renderPass;
        }

        const AZDescriptorPool& getDescriptorPool() const
        {
            return *descriptorPool;
        }

        const AZCommandBuffer& getCommandBuffer() const
        {
            return *commandBuffer;
        }

        std::vector<AZFramebuffer>& getSwapChainFramebuffers()
        {
            return swapChainFramebuffers;
        }

        void init(Window& window);
        void destroy();

    private:
        std::unique_ptr<AZInstance> instance;
        std::unique_ptr<PhysicalDevice> physicalDevice;
        std::unique_ptr<VulkanDevice> device;
        std::unique_ptr<AZDescriptorPool> descriptorPool;
        std::unique_ptr<AZSurface> surface;
        std::unique_ptr<AZSwapChain> swapChain;
        std::unique_ptr<AZRenderPass> renderPass;
        std::vector<AZFramebuffer> swapChainFramebuffers;
        std::unique_ptr<AZCommandPool> commandPool;
        std::unique_ptr<AZCommandBuffer> commandBuffer;

        VmaAllocator allocator { };
    };

    class ImGuiContext
    {
        void init(GLFWwindow* window);
        void destroy();
    };
}