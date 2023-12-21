#pragma once

#include "Window.h"
#include <vulkan/vulkan.hpp>

#include <vector>
#include <optional>

#include "render/rhi/vulkan/AZBuffer.h"
#include "render/rhi/vulkan/AZCommandBuffer.h"
#include "render/rhi/vulkan/AZCommandPool.h"
#include "render/rhi/vulkan/VKContext.h"
#include "render/rhi/vulkan/AZSwapChain.h"

struct GLFWwindow;

namespace Azazel
{
    class VkWindow : public Window
    {
    public:
        VkWindow(const WindowProperties& props);
        virtual ~VkWindow();
        void shutDown();
        void onUpdate(float delta) override;
        unsigned int getWidth() const override;
        unsigned int getHeight() const override;
        virtual void setEventCallback(const EventCallbackFn& callback) override;
        virtual void setVSync(bool enable) override;
        virtual bool isVSync() const override;
        virtual void* getNativeWindow() override;
    private:
        GLFWwindow* initGLFW(int width, int height, const std::string& title);
        void initGLFWCallbacks(GLFWwindow*);

        void initVulkan();

        VkSwapchainKHR createSwapChain(VkPhysicalDevice physicalDevice);
        
        std::vector<VkImageView> createImageViews(VkDevice, std::vector<VkImage>&);
        VkRenderPass createRenderPass(VkDevice device, VkFormat swapChainImageFormat);
        VkPipeline createGraphicsPipeline(VkDevice device);

        void drawFrame() override;

        VkShaderModule createShaderModule(VkDevice device, const std::vector<char>& code);

        std::vector<VkFramebuffer> createFramebuffers();

        AZCommandPool createCommandPool();

        void recordCommandBuffer(AZCommandBuffer & azCommandBuffer, uint32_t imageIndex);
        void createSyncObjects();
        void createDescriptorSetLayout();

        void destroyGLFW();
    private:

        GLFWwindow* window;
        int width;
        int height;
        std::string title;

        struct WindowData
        {
            EventCallbackFn eventCallback;
        };

        WindowData windowData;

        VkDevice device;

        std::vector<VkImageView> swapChainImageViews;
        std::vector<VkFramebuffer> swapChainFramebuffers;

        VkRenderPass renderPass;

        VkDescriptorSetLayout descriptorSetLayout;
        VkPipelineLayout pipelineLayout;
        VkPipeline graphicsPipeline;

        AZCommandPool commandPool;
        AZCommandBuffer commandBuffer;

        VkSemaphore imageAvailableSemaphore;
        VkSemaphore renderFinishedSemaphore;
        VkFence inFlightFence;

        VkDescriptorPool descriptorPool;

        AZSwapChain swapChain;
        VulkanDevice azDevice;
        VulkanSurface azSurface;
        VulkanContext context;
        PhysicalDevice azPhysicalDevice;
        AZVertexBuffer vertexBuffer;
        AZIndexBuffer indexBuffer;
    };
}
