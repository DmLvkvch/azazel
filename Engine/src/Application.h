#pragma once

#include "window/Window.h"
#include "LayerStack.h"
#include "camera/Camera.h"
#include <memory>

#include "render/rhi/vulkan/AZBuffer.h"
#include "render/rhi/vulkan/AZCommandBuffer.h"
#include "render/rhi/vulkan/AZInstance.h"
#include "render/rhi/vulkan/AZSurface.h"
#include "render/rhi/vulkan/AZDevice.h"
#include "render/rhi/vulkan/AZSwapChain.h"
#include "render/rhi/vulkan/AZRenderPass.h"
#include "render/rhi/vulkan/AZFramebuffer.h"
#include "render/rhi/vulkan/AZDescriptorSet.h"
#include <vulkan/vulkan.h>

namespace Azazel
{
    class Application
    {
    public:
        Application();
        ~Application();
        void run();
        void onEvent(Event& e);
        void pushLayer(Layer* layer);
        Window* getWindow();
        static Application* getApplication();
        unsigned long long subscribe(const std::function<void(Event&)>& func);
        unsigned long long subscribe(const std::function<void(float)>& func);

        void createTextureImage();
        void createImage(uint32_t width, uint32_t height, VkFormat format, VkImageTiling tiling, VkImageUsageFlags usage, VkMemoryPropertyFlags properties, VkImage& image, VkDeviceMemory& imageMemory);

        VkImageView createImageView(VkImage image, VkFormat format);

        void createTextureSampler();
        void createTextureImageView();
        void copyBufferToImage(VkBuffer buffer, VkImage image, uint32_t width, uint32_t height);

        void createDescriptorSets();

        void createDescriptorSetLayout();

        void updateUniformBuffer(uint32_t currentImage);

        VkShaderModule createShaderModule(VkDevice device, const std::vector<char>& code);

        VkPipeline createGraphicsPipeline(VkDevice device);

        std::vector<AZFramebuffer> createFramebuffers();

        void recordCommandBuffer(AZCommandBuffer& azCommandBuffer, uint32_t imageIndex);

        void createSyncObjects();

        void drawFrame();

        void transitionImageLayout(VkImage image, VkFormat format, VkImageLayout oldLayout, VkImageLayout newLayout);
        void createBuffer(PhysicalDevice& physicalDevice, VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VkBuffer& buffer, VkDeviceMemory& bufferMemory);

        VkPipeline graphicsPipeline;

        VkSemaphore imageAvailableSemaphore;
        VkSemaphore renderFinishedSemaphore;
        VkFence inFlightFence;

        std::vector<VkDescriptorSet> descriptorSets;

        VkDescriptorSetLayout descriptorSetLayout;
        VkPipelineLayout pipelineLayout;

        AZVertexBuffer vertexBuffer;
        AZIndexBuffer indexBuffer;
        AZUniformBuffer uniformBuffer;

        VkImageView textureImageView;
        VkImage textureImage;
        VkSampler textureSampler;
        VkDeviceMemory textureImageMemory;

        void unsubscribe(long long id);

    private:
        void updateTargets(float delta);
    private:
        unsigned long long id = 0;
        std::unique_ptr<Window> window;
        LayerStack layerStack;
        bool running = true;
        static Application* app;
        float delta;
        EventDispatcher<void, Event&> eventSubscribers;
        EventDispatcher<void , float> updateSubscribers;
        std::unique_ptr<Camera> camera;
    };
}