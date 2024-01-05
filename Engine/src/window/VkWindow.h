#pragma once

#include "Window.h"
#include <vulkan/vulkan.hpp>

#include <vector>
#include <optional>

#include "render/rhi/vulkan/AZBuffer.h"
#include "render/rhi/vulkan/AZCommandBuffer.h"
#include "render/rhi/vulkan/VKContext.h"
#include "render/rhi/vulkan/AZSurface.h"
#include "render/rhi/vulkan/AZDevice.h"
#include "render/rhi/vulkan/AZSwapChain.h"
#include "render/rhi/vulkan/AZRenderPass.h"
#include "render/rhi/vulkan/AZFramebuffer.h"

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
        
        void createDescriptoPool();
        void createDescriptorSets();
        void createDescriptorSetLayout();
        void updateUniformBuffer(uint32_t currentImage);
        VkPipeline createGraphicsPipeline(VkDevice device);

        void drawFrame() override;

        VkShaderModule createShaderModule(VkDevice device, const std::vector<char>& code);

        std::vector<AZFramebuffer> createFramebuffers();

        void recordCommandBuffer(AZCommandBuffer & azCommandBuffer, uint32_t imageIndex);
        void createSyncObjects();

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

        VkPipeline graphicsPipeline;

        AZCommandPool commandPool;
        AZCommandBuffer commandBuffer;

        VkSemaphore imageAvailableSemaphore;
        VkSemaphore renderFinishedSemaphore;
        VkFence inFlightFence;

        std::unique_ptr<AZSwapChain> swapChain;
        std::unique_ptr<AZSurface> surface;

        std::unique_ptr<VulkanDevice> device;
        std::unique_ptr<PhysicalDevice> physicalDevice;

        std::unique_ptr<VulkanContext> context;
        
        AZVertexBuffer vertexBuffer;
        AZIndexBuffer indexBuffer;

        AZRenderPass renderPass;
        std::vector<AZFramebuffer> swapChainFramebuffers;

        VkDescriptorPool descriptorPool;
        std::vector<VkDescriptorSet> descriptorSets;


        VkDescriptorSetLayout descriptorSetLayout;
        VkPipelineLayout pipelineLayout;

        AZUniformBuffer uniformBuffer;
    };
}
