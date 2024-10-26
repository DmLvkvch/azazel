#pragma once

#include <stdint.h>                             // for uint32_t
#include <vulkan/vulkan.h>
#include <vulkan/vulkan_core.h>                 // for VkDevice, VkPipeline
#include <functional>                           // for function
#include <memory>                               // for unique_ptr
#include <vector>                               // for vector

#include "LayerStack.h"                         // for LayerStack
#include "camera/Camera.h"
#include "events/Event.h"                       // for Event (ptr only), Eve...
#include "render/Model.h"                       // for Model
#include "render/rhi/vulkan/AZBuffer.h"
#include "render/rhi/vulkan/AZCommandBuffer.h"  // for AZCommandBuffer
#include "render/rhi/vulkan/AZDescriptorSet.h"
#include "render/rhi/vulkan/AZDevice.h"
#include "render/rhi/vulkan/AZFramebuffer.h"
#include "render/rhi/vulkan/AZImage.h"
#include "render/rhi/vulkan/AZInstance.h"
#include "render/rhi/vulkan/AZRenderPass.h"
#include "render/rhi/vulkan/AZSurface.h"
#include "render/rhi/vulkan/AZSwapChain.h"
#include "window/Window.h"

namespace Azazel
{
class AZImage;
class AZImageView;
class AZIndexBuffer;
class AZTextureSampler;
class AZUniformBuffer;
class AZVertexBuffer;
class Camera;
class Layer;
class Window;

    class Application
    {
    public:
        Application(Window& window);
        ~Application();
        void run();
        void onEvent(Event& e);
        void pushLayer(Layer* layer);
        Window* getWindow();
        static  void setApplication(Application* application);
        static Application* getApplication();
        unsigned long long subscribe(const std::function<void(Event&)>& func);
        unsigned long long subscribe(const std::function<void(float)>& func);

        void createDescriptorSets();

        void createDescriptorSetLayout();

        void updateUniformBuffer();

        VkShaderModule createShaderModule(VkDevice device, const std::vector<char>& code);

        VkPipeline createGraphicsPipeline(VkDevice device);

        void recordCommandBuffer(const AZCommandBuffer& azCommandBuffer, uint32_t imageIndex);

        void createSyncObjects();

        void drawFrame();


        VkPipeline graphicsPipeline;

        VkSemaphore imageAvailableSemaphore;
        VkSemaphore renderFinishedSemaphore;
        VkFence inFlightFence;

        std::vector<VkDescriptorSet> descriptorSets;

        VkDescriptorSetLayout descriptorSetLayout;
        VkPipelineLayout pipelineLayout;

        std::unique_ptr<AZVertexBuffer> vertexBuffer;
        std::unique_ptr<AZIndexBuffer> indexBuffer;
        std::unique_ptr<AZUniformBuffer> uniformBuffer;

        std::unique_ptr<AZImageView> textureImageView;
        std::unique_ptr<AZImage> textureImage;
        std::unique_ptr<AZTextureSampler> textureSampler;

        void unsubscribe(long long id);

    private:
        void updateTargets(float delta);
    private:
        unsigned long long id = 0;
        Window& window;
        LayerStack layerStack;
        bool running = true;
        static Application* app;
        float delta;
        EventDispatcher<void, Event&> eventSubscribers;
        EventDispatcher<void , float> updateSubscribers;
        std::unique_ptr<Camera> camera;
        
        Model cerberus;
    };
}