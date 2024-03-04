#include "VkWindow.h"

#include "events/ApplicationEvent.h"
#include "events/KeyEvent.h"
#include "events/MouseEvent.h"
#include <iostream>
#include "IO/KeyCodes.h"

#include <fstream>
#include <stdexcept>
#include <algorithm>
#include <cstring>
#include <cstdlib>
#include <cstdint>
#include <limits>
#include <optional>
#include <set>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <chrono>
#include <stb_image/stb_image.h>

#include "render/Vertex.h"

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_vulkan.h>
#define GLFW_INCLUDE_NONE
#define GLFW_INCLUDE_VULKAN

namespace Azazel
{

    const std::vector<Vertex> vertices = {
        {{-0.5f, -0.5f, 0.0f}, {1.0f, 0.0f, 0.0f}, {0.0f, 0.0f}},
        {{0.5f, -0.5f, 0.0f}, {0.0f, 1.0f, 0.0f}, {1.0f, 0.0f}},
        {{0.5f, 0.5f, 0.0f}, {0.0f, 0.0f, 1.0f}, {1.0f, 1.0f}},
        {{-0.5f, 0.5f, 0.0f}, {1.0f, 1.0f, 1.0f}, {0.0f, 1.0f}},

        {{-0.5f, -0.5f, -0.5f}, {1.0f, 0.0f, 0.0f}, {0.0f, 0.0f}},
        {{0.5f, -0.5f, -0.5f}, {0.0f, 1.0f, 0.0f}, {1.0f, 0.0f}},
        {{0.5f, 0.5f, -0.5f}, {0.0f, 0.0f, 1.0f}, {1.0f, 1.0f}},
        {{-0.5f, 0.5f, -0.5f}, {1.0f, 1.0f, 1.0f}, {0.0f, 1.0f}}
    };

    const std::vector<uint32_t> indices = {
        0, 1, 2, 2, 3, 0,
        4, 5, 6, 6, 7, 4
    };

    static bool initialized = false;

    const int MAX_FRAMES_IN_FLIGHT = 2;

    std::vector<const char*> validationLayers =
    {
        "VK_LAYER_KHRONOS_validation"
    };

    std::vector<const char*> deviceExtensions =
    {
        VK_KHR_SWAPCHAIN_EXTENSION_NAME,
        #ifndef _WIN32
        "VK_KHR_portability_subset"
        #endif
    };

    VkWindow::VkWindow(const WindowProperties& props)
    {
        this->width = props.width;
        this->height = props.height;
        this->title = props.title;
        window = initGLFW(props.width, props.height, props.title);
        initGLFWCallbacks(window);

        initVulkan();
    }

    GLFWwindow* VkWindow::initGLFW(int width, int height, const std::string& title)
    {
        glfwInit();

        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
        glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

        GLFWwindow* window =  glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
        glfwSetWindowUserPointer(window, &windowData);
        return window;
    }

    void VkWindow::initGLFWCallbacks(GLFWwindow* window)
    {
        glfwSetWindowCloseCallback(window, [](GLFWwindow* window)
        {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
            WindowCloseEvent e;
            data.eventCallback(e);
        });

        glfwSetWindowSizeCallback(window, [](GLFWwindow* window, int w, int h)
        {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
            WindowResizeEvent e(w, h);
            data.eventCallback(e);
        });

        glfwSetKeyCallback(window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
        {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
            switch(action)
            {
                case GLFW_PRESS:
                {
                    KeyPressedEvent e(key, 1);
                    data.eventCallback(e);
                    if (key == KEY_ESCAPE)
                    {
                        WindowCloseEvent ev {};
                        data.eventCallback(ev);
                    }
                    break;
                }
                case GLFW_RELEASE:
                {
                    KeyReleasedEvent e(key);
                    data.eventCallback(e);
                    break;
                }
                case GLFW_REPEAT:
                {
                    KeyPressedEvent e(key, 1);
                    data.eventCallback(e);
                    break;
                }
            }
        });

        glfwSetMouseButtonCallback(window, [](GLFWwindow* window, int button, int action, int mods)
        {
            WindowData& data = *(WindowData*) glfwGetWindowUserPointer(window);
            switch (action)
            {
                case GLFW_PRESS:
                {
                    MouseButtonPressedEvent e(button);
                    data.eventCallback(e);
                    break;
                }
                case GLFW_RELEASE:
                {
                    MouseButtonReleasedEvent e(button);
                    data.eventCallback(e);
                    break;
                }
            }
        });

        glfwSetScrollCallback(window, [](GLFWwindow* window, double xOffset, double yOffset)
        {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
            MouseScrollEvent e(static_cast<float> (xOffset), static_cast<float> (yOffset));
            data.eventCallback(e);
        });

        glfwSetCursorPosCallback(window, [](GLFWwindow* window, double xPos, double yPos)
        {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
            MouseMovedEvent e((float) xPos, (float) yPos);
            data.eventCallback(e);
        });
    }

    struct UniformBufferObject 
    {
        glm::mat4 model;
        glm::mat4 view;
        glm::mat4 proj;
    };

    static ImGui_ImplVulkanH_Window g_MainWindowData;

    void VkWindow::initVulkan()
    {
        
        instance = std::make_unique<AZInstance>();

        surface = std::make_unique<AZSurface>(instance->instance, window);

        physicalDevice = std::make_unique<PhysicalDevice>(instance->instance, surface->surface);

        device = std::make_unique<VulkanDevice>(*instance, *physicalDevice);

        swapChain = std::make_unique<AZSwapChain>(window, *surface, *physicalDevice, *device);

        renderPass = std::make_unique<AZRenderPass>(device->device, swapChain->swapChainImageFormat);
        
        swapChainFramebuffers = createFramebuffers();

        uniformBuffer = AZUniformBuffer(device->device, *physicalDevice, sizeof(UniformBufferObject), nullptr);

        commandPool = std::make_unique<AZCommandPool>(device->device, physicalDevice->indices.graphicsFamily.value());

        createTextureImage();
        createTextureImageView();
        createTextureSampler();

        createDescriptorSetLayout();
        createDescriptoPool();
        createDescriptorSets();

        graphicsPipeline = createGraphicsPipeline(device->device);
                                                    
        vertexBuffer = AZVertexBuffer(device->device, *physicalDevice, commandPool->commandPool, device->graphicsQueue.queue, BufferDesc{ (void*)vertices.data(), sizeof(vertices[0]) * vertices.size() } );

        indexBuffer = AZIndexBuffer(device->device, *physicalDevice, commandPool->commandPool, device->graphicsQueue.queue, (void*) indices.data(), indices.size());

        commandBuffer = std::unique_ptr<AZCommandBuffer>(commandPool->allocateCommandBuffer(device->device));
        createSyncObjects();

        VkPresentModeKHR presentMode = VK_PRESENT_MODE_MAILBOX_KHR;

        g_MainWindowData.Surface = surface->surface;
        g_MainWindowData.SurfaceFormat = swapChain->surfaceFormat;

        g_MainWindowData.PresentMode = ImGui_ImplVulkanH_SelectPresentMode(physicalDevice->physicalDevice, surface->surface, &presentMode, 1);

        ImGui_ImplVulkanH_CreateOrResizeWindow(instance->instance, physicalDevice->physicalDevice, device->device, &g_MainWindowData, device->graphicsQueue.queueFamilyIndex, nullptr, width, height, 2);

        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO(); (void)io;
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;

        ImGui::StyleColorsDark();

        ImGui_ImplGlfw_InitForVulkan(window, true);
        ImGui_ImplVulkan_InitInfo init_info{};
        init_info.Instance = instance->instance;
        init_info.PhysicalDevice = physicalDevice->physicalDevice;
        init_info.Device = device->device;
        init_info.QueueFamily = device->graphicsQueue.queueFamilyIndex;
        init_info.Queue = device->graphicsQueue.queue;
        init_info.PipelineCache = nullptr;
        init_info.DescriptorPool = descriptorPool;
        init_info.Subpass = 0;
        init_info.RenderPass = g_MainWindowData.RenderPass;
        init_info.MinImageCount = 2;
        init_info.ImageCount = g_MainWindowData.ImageCount;
        init_info.MSAASamples = VK_SAMPLE_COUNT_1_BIT;
        init_info.Allocator = nullptr;
        init_info.CheckVkResultFn = nullptr;
        ImGui_ImplVulkan_Init(&init_info);

    }

    void VkWindow::createTextureImage()
    {
        int texWidth, texHeight, texChannels;
        unsigned char* pixels = stbi_load("textures/awesomeface.png", &texWidth, &texHeight, &texChannels, STBI_rgb_alpha);
        VkDeviceSize imageSize = texWidth * texHeight * 4;

        if (!pixels) 
        {
            throw std::runtime_error("failed to load texture image!");
        }

        VkBuffer stagingBuffer;
        VkDeviceMemory stagingBufferMemory;
        createBuffer(*physicalDevice, imageSize, VK_BUFFER_USAGE_TRANSFER_SRC_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, stagingBuffer, stagingBufferMemory);

        void* data;
        vkMapMemory(device->device, stagingBufferMemory, 0, imageSize, 0, &data);
            memcpy(data, pixels, static_cast<size_t>(imageSize));
        vkUnmapMemory(device->device, stagingBufferMemory);

        stbi_image_free(pixels);

        createImage(texWidth, texHeight, VK_FORMAT_R8G8B8A8_SRGB, VK_IMAGE_TILING_OPTIMAL, VK_IMAGE_USAGE_TRANSFER_DST_BIT | VK_IMAGE_USAGE_SAMPLED_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, textureImage, textureImageMemory);

        transitionImageLayout(textureImage, VK_FORMAT_R8G8B8A8_SRGB, VK_IMAGE_LAYOUT_UNDEFINED, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL);
            copyBufferToImage(stagingBuffer, textureImage, static_cast<uint32_t>(texWidth), static_cast<uint32_t>(texHeight));
        transitionImageLayout(textureImage, VK_FORMAT_R8G8B8A8_SRGB, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL);

        vkDestroyBuffer(device->device, stagingBuffer, nullptr);
        vkFreeMemory(device->device, stagingBufferMemory, nullptr);
    }

    void VkWindow::createBuffer(PhysicalDevice& physicalDevice, VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VkBuffer& buffer, VkDeviceMemory& bufferMemory)
    {
        VkBufferCreateInfo bufferInfo{};
        bufferInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
        bufferInfo.size = size;
        bufferInfo.usage = usage;
        bufferInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;

        vkCreateBuffer(device->device, &bufferInfo, nullptr, &buffer);

        VkMemoryRequirements memRequirements;
        vkGetBufferMemoryRequirements(device->device, buffer, &memRequirements);

        VkMemoryAllocateInfo allocInfo{};
        allocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
        allocInfo.allocationSize = memRequirements.size;
        allocInfo.memoryTypeIndex = physicalDevice.findMemoryType(memRequirements.memoryTypeBits, properties);

        vkAllocateMemory(device->device, &allocInfo, nullptr, &bufferMemory);

        vkBindBufferMemory(device->device, buffer, bufferMemory, 0);
    }

    void VkWindow::createTextureImageView() 
    {
        textureImageView = createImageView(textureImage, VK_FORMAT_R8G8B8A8_SRGB);
    }

    void VkWindow::createTextureSampler() 
    {
        VkPhysicalDeviceProperties properties{};
        vkGetPhysicalDeviceProperties(physicalDevice->physicalDevice, &properties);

        VkSamplerCreateInfo samplerInfo{};
        samplerInfo.sType = VK_STRUCTURE_TYPE_SAMPLER_CREATE_INFO;
        samplerInfo.magFilter = VK_FILTER_LINEAR;
        samplerInfo.minFilter = VK_FILTER_LINEAR;
        samplerInfo.addressModeU = VK_SAMPLER_ADDRESS_MODE_REPEAT;
        samplerInfo.addressModeV = VK_SAMPLER_ADDRESS_MODE_REPEAT;
        samplerInfo.addressModeW = VK_SAMPLER_ADDRESS_MODE_REPEAT;
        samplerInfo.anisotropyEnable = VK_TRUE;
        samplerInfo.maxAnisotropy = properties.limits.maxSamplerAnisotropy;
        samplerInfo.borderColor = VK_BORDER_COLOR_INT_OPAQUE_BLACK;
        samplerInfo.unnormalizedCoordinates = VK_FALSE;
        samplerInfo.compareEnable = VK_FALSE;
        samplerInfo.compareOp = VK_COMPARE_OP_ALWAYS;
        samplerInfo.mipmapMode = VK_SAMPLER_MIPMAP_MODE_LINEAR;

        if (vkCreateSampler(device->device, &samplerInfo, nullptr, &textureSampler) != VK_SUCCESS)
         {
            throw std::runtime_error("failed to create texture sampler!");
        }
    }

    VkImageView VkWindow::createImageView(VkImage image, VkFormat format)
    {
        VkImageViewCreateInfo viewInfo{};
        viewInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
        viewInfo.image = image;
        viewInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
        viewInfo.format = format;
        viewInfo.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
        viewInfo.subresourceRange.baseMipLevel = 0;
        viewInfo.subresourceRange.levelCount = 1;
        viewInfo.subresourceRange.baseArrayLayer = 0;
        viewInfo.subresourceRange.layerCount = 1;

        VkImageView imageView;
        if (vkCreateImageView(device->device, &viewInfo, nullptr, &imageView) != VK_SUCCESS)
        {
            throw std::runtime_error("failed to create texture image view!");
        }

        return imageView;
    }

    void VkWindow::createImage(uint32_t width, uint32_t height, VkFormat format, VkImageTiling tiling, VkImageUsageFlags usage, VkMemoryPropertyFlags properties, VkImage& image, VkDeviceMemory& imageMemory) {
        VkImageCreateInfo imageInfo{};
        imageInfo.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
        imageInfo.imageType = VK_IMAGE_TYPE_2D;
        imageInfo.extent.width = width;
        imageInfo.extent.height = height;
        imageInfo.extent.depth = 1;
        imageInfo.mipLevels = 1;
        imageInfo.arrayLayers = 1;
        imageInfo.format = format;
        imageInfo.tiling = tiling;
        imageInfo.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
        imageInfo.usage = usage;
        imageInfo.samples = VK_SAMPLE_COUNT_1_BIT;
        imageInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;

        if (vkCreateImage(device->device, &imageInfo, nullptr, &image) != VK_SUCCESS)
        {
            throw std::runtime_error("failed to create image!");
        }

        VkMemoryRequirements memRequirements;
        vkGetImageMemoryRequirements(device->device, image, &memRequirements);

        VkMemoryAllocateInfo allocInfo{};
        allocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
        allocInfo.allocationSize = memRequirements.size;
        allocInfo.memoryTypeIndex = physicalDevice->findMemoryType(memRequirements.memoryTypeBits, properties);

        if (vkAllocateMemory(device->device, &allocInfo, nullptr, &imageMemory) != VK_SUCCESS) 
        {
            throw std::runtime_error("failed to allocate image memory!");
        }

        vkBindImageMemory(device->device, image, imageMemory, 0);
    }

    void VkWindow::transitionImageLayout(VkImage image, VkFormat format, VkImageLayout oldLayout, VkImageLayout newLayout) 
    {
        VkCommandBuffer commandBuffer = AZCommandBuffer::beginSingleTimeCommands(*device, *commandPool);

        VkImageMemoryBarrier barrier{};
        barrier.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
        barrier.oldLayout = oldLayout;
        barrier.newLayout = newLayout;
        barrier.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
        barrier.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
        barrier.image = image;
        barrier.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
        barrier.subresourceRange.baseMipLevel = 0;
        barrier.subresourceRange.levelCount = 1;
        barrier.subresourceRange.baseArrayLayer = 0;
        barrier.subresourceRange.layerCount = 1;

        VkPipelineStageFlags sourceStage;
        VkPipelineStageFlags destinationStage;

        if (oldLayout == VK_IMAGE_LAYOUT_UNDEFINED && newLayout == VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL)
        {
            barrier.srcAccessMask = 0;
            barrier.dstAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;

            sourceStage = VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT;
            destinationStage = VK_PIPELINE_STAGE_TRANSFER_BIT;
        } 
        else if (oldLayout == VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL && newLayout == VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL) 
        {
            barrier.srcAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;
            barrier.dstAccessMask = VK_ACCESS_SHADER_READ_BIT;

            sourceStage = VK_PIPELINE_STAGE_TRANSFER_BIT;
            destinationStage = VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT;
        }
        else
        {
            throw std::invalid_argument("unsupported layout transition!");
        }

        vkCmdPipelineBarrier(commandBuffer, sourceStage, destinationStage, 0, 0, nullptr, 0, nullptr, 1, &barrier);

        AZCommandBuffer::endSingleTimeCommands(*device, *commandPool, commandBuffer);
    }

    void VkWindow::copyBufferToImage(VkBuffer buffer, VkImage image, uint32_t width, uint32_t height)
    {
        VkCommandBuffer commandBuffer = AZCommandBuffer::beginSingleTimeCommands(*device, *commandPool);
        VkBufferImageCopy region{};
        region.bufferOffset = 0;
        region.bufferRowLength = 0;
        region.bufferImageHeight = 0;
        region.imageSubresource.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
        region.imageSubresource.mipLevel = 0;
        region.imageSubresource.baseArrayLayer = 0;
        region.imageSubresource.layerCount = 1;
        region.imageOffset = {0, 0, 0};
        region.imageExtent = { width, height, 1 };

        vkCmdCopyBufferToImage(commandBuffer, buffer, image, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, 1, &region);

        AZCommandBuffer::endSingleTimeCommands(*device, *commandPool, commandBuffer);
    }

    static std::vector<char> readFile(const std::string& filename)
    {
        std::ifstream file(filename, std::ios::ate | std::ios::binary);

        if (!file.is_open())
        {
            throw std::runtime_error("failed to open file!");
        }

        size_t fileSize = (size_t) file.tellg();
        std::vector<char> buffer(fileSize);

        file.seekg(0);
        file.read(buffer.data(), fileSize);

        file.close();

        return buffer;
    }

    void VkWindow::createDescriptoPool()
    {
        std::array<VkDescriptorPoolSize, 11> pool_sizes 
        {{
            {VK_DESCRIPTOR_TYPE_SAMPLER, 2048},
            {VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, 2048},
            {VK_DESCRIPTOR_TYPE_SAMPLED_IMAGE, 2048},
            {VK_DESCRIPTOR_TYPE_STORAGE_IMAGE, 2048},
            {VK_DESCRIPTOR_TYPE_UNIFORM_TEXEL_BUFFER, 2048},
            {VK_DESCRIPTOR_TYPE_STORAGE_TEXEL_BUFFER, 2048},
            {VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, 2048},
            {VK_DESCRIPTOR_TYPE_STORAGE_BUFFER, 2048},
            {VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER_DYNAMIC, 2048},
            {VK_DESCRIPTOR_TYPE_STORAGE_BUFFER_DYNAMIC, 2048},
            {VK_DESCRIPTOR_TYPE_INPUT_ATTACHMENT, 2048}
        }};

        VkDescriptorPoolCreateInfo poolInfo = {};
        poolInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
        poolInfo.flags = VK_DESCRIPTOR_POOL_CREATE_FREE_DESCRIPTOR_SET_BIT;
        poolInfo.maxSets = 2048 * pool_sizes.size();
        poolInfo.poolSizeCount = pool_sizes.size();
        poolInfo.pPoolSizes = pool_sizes.data();

        vkCreateDescriptorPool(device->device, &poolInfo, nullptr, &descriptorPool);
    }
    
    void VkWindow::createDescriptorSets()
    {
        std::vector<VkDescriptorSetLayout> layouts(MAX_FRAMES_IN_FLIGHT, descriptorSetLayout);
        VkDescriptorSetAllocateInfo allocInfo {};
        allocInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
        allocInfo.descriptorPool = descriptorPool;
        allocInfo.descriptorSetCount = static_cast<uint32_t>(MAX_FRAMES_IN_FLIGHT);
        allocInfo.pSetLayouts = layouts.data();

        descriptorSets.resize(MAX_FRAMES_IN_FLIGHT);
        vkAllocateDescriptorSets(device->device, &allocInfo, descriptorSets.data());

        for (size_t i = 0; i < MAX_FRAMES_IN_FLIGHT; i++) 
        {
            VkDescriptorBufferInfo bufferInfo{};
            bufferInfo.buffer = uniformBuffer.uniformBuffer;
            bufferInfo.offset = 0;
            bufferInfo.range = sizeof(UniformBufferObject);

            VkDescriptorImageInfo imageInfo{};
            imageInfo.imageLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
            imageInfo.imageView = textureImageView;
            imageInfo.sampler = textureSampler;

            std::array<VkWriteDescriptorSet, 2> descriptorWrites{};

            descriptorWrites[0].sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
            descriptorWrites[0].dstSet = descriptorSets[i];
            descriptorWrites[0].dstBinding = 0;
            descriptorWrites[0].dstArrayElement = 0;
            descriptorWrites[0].descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
            descriptorWrites[0].descriptorCount = 1;
            descriptorWrites[0].pBufferInfo = &bufferInfo;

            descriptorWrites[1].sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
            descriptorWrites[1].dstSet = descriptorSets[i];
            descriptorWrites[1].dstBinding = 1;
            descriptorWrites[1].dstArrayElement = 0;
            descriptorWrites[1].descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
            descriptorWrites[1].descriptorCount = 1;
            descriptorWrites[1].pImageInfo = &imageInfo;

            vkUpdateDescriptorSets(device->device, static_cast<uint32_t>(descriptorWrites.size()), descriptorWrites.data(), 0, nullptr);
        }
    }

    void VkWindow::createDescriptorSetLayout()
    {
        VkDescriptorSetLayoutBinding uboLayoutBinding {};
        uboLayoutBinding.binding = 0;
        uboLayoutBinding.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
        uboLayoutBinding.descriptorCount = 1;
        uboLayoutBinding.pImmutableSamplers = nullptr;
        uboLayoutBinding.stageFlags = VK_SHADER_STAGE_VERTEX_BIT;

        VkDescriptorSetLayoutBinding samplerLayoutBinding{};
        samplerLayoutBinding.binding = 1;
        samplerLayoutBinding.descriptorCount = 1;
        samplerLayoutBinding.descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
        samplerLayoutBinding.pImmutableSamplers = nullptr;
        samplerLayoutBinding.stageFlags = VK_SHADER_STAGE_FRAGMENT_BIT;

        std::array<VkDescriptorSetLayoutBinding, 2> bindings = {uboLayoutBinding, samplerLayoutBinding};
        VkDescriptorSetLayoutCreateInfo layoutInfo{};
        layoutInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
        layoutInfo.bindingCount = static_cast<uint32_t>(bindings.size());
        layoutInfo.pBindings = bindings.data();

        vkCreateDescriptorSetLayout(device->device, &layoutInfo, nullptr, &descriptorSetLayout);
    }

    void VkWindow::updateUniformBuffer(uint32_t currentImage)
    {
        static auto startTime = std::chrono::high_resolution_clock::now();

        auto currentTime = std::chrono::high_resolution_clock::now();
        float time = std::chrono::duration<float, std::chrono::seconds::period>(currentTime - startTime).count();

        UniformBufferObject ubo {};
        ubo.model = glm::rotate(glm::mat4(1.0f), time * glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
        ubo.view = glm::lookAt(glm::vec3(2.0f, 2.0f, 2.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
        ubo.proj = glm::perspective(glm::radians(45.0f), 1.5f, 0.1f, 10.0f);
        ubo.proj[1][1] *= -1;

        uniformBuffer.updateData(&ubo, sizeof(UniformBufferObject));
    }

    VkShaderModule VkWindow::createShaderModule(VkDevice device, const std::vector<char>& code)
    {
        VkShaderModuleCreateInfo createInfo {};
        {
            createInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
            createInfo.codeSize = code.size();
            createInfo.pCode = reinterpret_cast<const uint32_t*>(code.data());
        }
        VkShaderModule shaderModule;
        vkCreateShaderModule(device, &createInfo, nullptr, &shaderModule);

        return shaderModule;
    }

    VkPipeline VkWindow::createGraphicsPipeline(VkDevice device)
    {
        auto vertShaderCode = readFile("shaders/example.vert.spv");
        auto fragShaderCode = readFile("shaders/example.frag.spv");

        VkShaderModule vertShaderModule = createShaderModule(device, vertShaderCode);
        VkShaderModule fragShaderModule = createShaderModule(device, fragShaderCode);

        VkPipelineShaderStageCreateInfo vertShaderStageInfo{};
        vertShaderStageInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
        vertShaderStageInfo.stage = VK_SHADER_STAGE_VERTEX_BIT;
        vertShaderStageInfo.module = vertShaderModule;
        vertShaderStageInfo.pName = "main";

        VkPipelineShaderStageCreateInfo fragShaderStageInfo{};
        fragShaderStageInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
        fragShaderStageInfo.stage = VK_SHADER_STAGE_FRAGMENT_BIT;
        fragShaderStageInfo.module = fragShaderModule;
        fragShaderStageInfo.pName = "main";

        VkPipelineShaderStageCreateInfo shaderStages[] = {vertShaderStageInfo, fragShaderStageInfo};

        VkPipelineVertexInputStateCreateInfo vertexInputInfo {};
        vertexInputInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;

        auto bindingDescription = Vertex::getBindingDescription();
        auto attributeDescriptions = Vertex::getAttributeDescriptions();

        vertexInputInfo.vertexBindingDescriptionCount = 1;
        vertexInputInfo.vertexAttributeDescriptionCount = static_cast<uint32_t>(attributeDescriptions.size());
        vertexInputInfo.pVertexBindingDescriptions = &bindingDescription;
        vertexInputInfo.pVertexAttributeDescriptions = attributeDescriptions.data();

        VkPipelineInputAssemblyStateCreateInfo inputAssembly {};
        inputAssembly.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
        inputAssembly.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
        inputAssembly.primitiveRestartEnable = VK_FALSE;

        VkPipelineViewportStateCreateInfo viewportState{};
        viewportState.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
        viewportState.viewportCount = 1;
        viewportState.scissorCount = 1;

        VkPipelineRasterizationStateCreateInfo rasterizer {};
        rasterizer.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
        rasterizer.depthClampEnable = VK_FALSE;
        rasterizer.rasterizerDiscardEnable = VK_FALSE;
        rasterizer.polygonMode = VK_POLYGON_MODE_FILL;
        rasterizer.lineWidth = 1.0f;
        rasterizer.cullMode = VK_CULL_MODE_BACK_BIT;
        rasterizer.frontFace = VK_FRONT_FACE_COUNTER_CLOCKWISE;
        rasterizer.depthBiasEnable = VK_FALSE;

        VkPipelineMultisampleStateCreateInfo multisampling {};
        multisampling.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
        multisampling.sampleShadingEnable = VK_FALSE;
        multisampling.rasterizationSamples = VK_SAMPLE_COUNT_1_BIT;

        VkPipelineColorBlendAttachmentState colorBlendAttachment {};
        colorBlendAttachment.colorWriteMask = VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT | VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT;
        colorBlendAttachment.blendEnable = VK_TRUE;
        colorBlendAttachment.srcColorBlendFactor = VK_BLEND_FACTOR_SRC_ALPHA;
        colorBlendAttachment.dstColorBlendFactor = VK_BLEND_FACTOR_ONE_MINUS_SRC_ALPHA;
        colorBlendAttachment.colorBlendOp = VK_BLEND_OP_ADD;
        colorBlendAttachment.srcAlphaBlendFactor = VK_BLEND_FACTOR_SRC_ALPHA;
        colorBlendAttachment.dstAlphaBlendFactor = VK_BLEND_FACTOR_ONE_MINUS_SRC_ALPHA;
        colorBlendAttachment.alphaBlendOp = VK_BLEND_OP_ADD;
        VkPipelineColorBlendStateCreateInfo colorBlending{};
        colorBlending.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
        colorBlending.logicOpEnable = VK_FALSE;
        colorBlending.logicOp = VK_LOGIC_OP_COPY;
        colorBlending.attachmentCount = 1;
        colorBlending.pAttachments = &colorBlendAttachment;
        colorBlending.blendConstants[0] = 0.0f;
        colorBlending.blendConstants[1] = 0.0f;
        colorBlending.blendConstants[2] = 0.0f;
        colorBlending.blendConstants[3] = 0.0f;

        std::vector<VkDynamicState> dynamicStates = 
        {
            VK_DYNAMIC_STATE_VIEWPORT,
            VK_DYNAMIC_STATE_SCISSOR
        };

        VkPipelineDynamicStateCreateInfo dynamicState {};
        dynamicState.sType = VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO;
        dynamicState.dynamicStateCount = static_cast<uint32_t>(dynamicStates.size());
        dynamicState.pDynamicStates = dynamicStates.data();        

        VkPipelineLayoutCreateInfo pipelineLayoutInfo {};
        pipelineLayoutInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
        pipelineLayoutInfo.setLayoutCount = 1;
        pipelineLayoutInfo.pSetLayouts = &descriptorSetLayout;

        vkCreatePipelineLayout(device, &pipelineLayoutInfo, nullptr, &pipelineLayout);

        VkGraphicsPipelineCreateInfo pipelineInfo{};
        pipelineInfo.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
        pipelineInfo.stageCount = 2;
        pipelineInfo.pStages = shaderStages;
        pipelineInfo.pVertexInputState = &vertexInputInfo;
        pipelineInfo.pInputAssemblyState = &inputAssembly;
        pipelineInfo.pViewportState = &viewportState;
        pipelineInfo.pRasterizationState = &rasterizer;
        pipelineInfo.pMultisampleState = &multisampling;
        pipelineInfo.pColorBlendState = &colorBlending;
        pipelineInfo.pDynamicState = &dynamicState;
        pipelineInfo.layout = pipelineLayout;
        pipelineInfo.renderPass = renderPass->renderPass;
        pipelineInfo.subpass = 0;
        pipelineInfo.basePipelineHandle = VK_NULL_HANDLE;

        vkCreateGraphicsPipelines(device, VK_NULL_HANDLE, 1, &pipelineInfo, nullptr, &graphicsPipeline);

        vkDestroyShaderModule(device, fragShaderModule, nullptr);
        vkDestroyShaderModule(device, vertShaderModule, nullptr);
        return graphicsPipeline;
    }

    std::vector<AZFramebuffer> VkWindow::createFramebuffers()
    {
        std::vector<AZFramebuffer> swapChainFramebuffers;

        auto& swapChainImageViews = swapChain->swapChainImageViews;
        swapChainFramebuffers.resize(swapChainImageViews.size());

        for (size_t i = 0; i < swapChainImageViews.size(); i++)
        {
            uint32_t width = swapChain->swapChainExtent.width;
            uint32_t height = swapChain->swapChainExtent.height;
            auto& imageView = swapChainImageViews[i];
            AZFramebufferDesc fboDesc { {imageView}, renderPass->renderPass, width, height };
            AZFramebuffer fb(device->device, fboDesc);
            swapChainFramebuffers[i] = fb;
        }
        return swapChainFramebuffers;
    }

    void VkWindow::recordCommandBuffer(AZCommandBuffer& azCommandBuffer, uint32_t imageIndex)
    {
        
        VkCommandBuffer commandBuffer = azCommandBuffer.commandBuffer;

        //renderPass->beginRenderPass(azCommandBuffer, swapChainFramebuffers[imageIndex].framebuffer, swapChain->swapChainExtent);

        vkCmdBindPipeline(commandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, graphicsPipeline);

        VkViewport viewport{};
        viewport.x = 0.0f;
        viewport.y = 0.0f;
        viewport.width = (float) swapChain->swapChainExtent.width;
        viewport.height = (float) swapChain->swapChainExtent.height;
        viewport.minDepth = 0.0f;
        viewport.maxDepth = 1.0f;

        vkCmdSetViewport(commandBuffer, 0, 1, &viewport);

        VkRect2D scissor {};
        scissor.offset = {0, 0};
        scissor.extent = swapChain->swapChainExtent;

        vkCmdSetScissor(commandBuffer, 0, 1, &scissor);            

        VkBuffer vertexBuffers[] = {vertexBuffer.vertexBuffer};
        VkDeviceSize offsets[] = {0};

        vkCmdBindVertexBuffers(commandBuffer, 0, 1, vertexBuffers, offsets);

        vkCmdBindIndexBuffer(commandBuffer, indexBuffer.indexBuffer, 0, VK_INDEX_TYPE_UINT32);

        vkCmdBindDescriptorSets(commandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, pipelineLayout, 0, 1, &descriptorSets[imageIndex % MAX_FRAMES_IN_FLIGHT], 0, nullptr);
        vkCmdDrawIndexed(commandBuffer, static_cast<uint32_t>(indices.size()), 1, 0, 0, 0);

        //renderPass->endRenderPass(azCommandBuffer);

    }

    void VkWindow::createSyncObjects()
    {
        VkSemaphoreCreateInfo semaphoreInfo {};
        {
            semaphoreInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;
        }

        VkFenceCreateInfo fenceInfo {};
        {
            fenceInfo.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
            fenceInfo.flags = VK_FENCE_CREATE_SIGNALED_BIT;
        }

        vkCreateSemaphore(device->device, &semaphoreInfo, nullptr, &imageAvailableSemaphore);
        vkCreateSemaphore(device->device, &semaphoreInfo, nullptr, &renderFinishedSemaphore);
        vkCreateFence(device->device, &fenceInfo, nullptr, &inFlightFence);
    }

    void VkWindow::drawFrame() 
    {
        VkDevice device = this->device->device;
        vkWaitForFences(device, 1, &inFlightFence, VK_TRUE, UINT64_MAX);
        vkResetFences(device, 1, &inFlightFence);

        uint32_t imageIndex;
        vkAcquireNextImageKHR(device, swapChain->swapChain, UINT64_MAX, imageAvailableSemaphore, VK_NULL_HANDLE, &imageIndex);

        updateUniformBuffer(imageIndex % MAX_FRAMES_IN_FLIGHT);

        commandBuffer->reset();
        commandBuffer->begin();
        renderPass->beginRenderPass(*commandBuffer, swapChainFramebuffers[imageIndex].framebuffer, swapChain->swapChainExtent);
        
        recordCommandBuffer(*commandBuffer, imageIndex);

        ImGui_ImplVulkan_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();


        ImGui::Begin("Hello, world!");
        ImGui::Text("This is some useful text.");
        ImGui::Button("Button");
        ImGui::SameLine();
        ImGui::Text("counter = %d", 111);
        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f, 123.0f);
        ImGui::End();
        

        ImGui::Render();
        ImDrawData* draw_data = ImGui::GetDrawData();
        g_MainWindowData.ClearValue.color.float32[0] = 1;
        g_MainWindowData.ClearValue.color.float32[1] = 1;
        g_MainWindowData.ClearValue.color.float32[2] = 1;
        g_MainWindowData.ClearValue.color.float32[3] = 1;
        
        ImGui_ImplVulkan_RenderDrawData(draw_data, commandBuffer->commandBuffer);

        renderPass->endRenderPass(*commandBuffer);

        commandBuffer->end();

        VkSubmitInfo submitInfo {};
        submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;

        VkSemaphore waitSemaphores[] = {imageAvailableSemaphore};
        VkPipelineStageFlags waitStages[] = {VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT};
        submitInfo.waitSemaphoreCount = 1;
        submitInfo.pWaitSemaphores = waitSemaphores;
        submitInfo.pWaitDstStageMask = waitStages;

        submitInfo.commandBufferCount = 1;
        submitInfo.pCommandBuffers = &commandBuffer->commandBuffer;

        VkSemaphore signalSemaphores[] = {renderFinishedSemaphore};
        submitInfo.signalSemaphoreCount = 1;
        submitInfo.pSignalSemaphores = signalSemaphores;

        this->device->graphicsQueue.submit(1, &submitInfo, inFlightFence);

        VkPresentInfoKHR presentInfo{};
        presentInfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;

        presentInfo.waitSemaphoreCount = 1;
        presentInfo.pWaitSemaphores = signalSemaphores;

        presentInfo.swapchainCount = 1;
        presentInfo.pSwapchains = &swapChain->swapChain;

        presentInfo.pImageIndices = &imageIndex;

        vkQueuePresentKHR(this->device->presentQueue.queue, &presentInfo);
    }

    VkWindow::~VkWindow()
    {
        
    }

    void VkWindow::destroyGLFW()
    {
        glfwDestroyWindow(window);
        glfwTerminate();
    }

    void VkWindow::shutDown()
    {

    }

    void VkWindow::onUpdate(float delta)
    {
        glfwPollEvents();
    }

    unsigned int VkWindow::getWidth() const
    {
        return width;
    }

    unsigned int VkWindow::getHeight() const
    {
        return height;
    }

    void VkWindow::setEventCallback(const EventCallbackFn& callback)
    {
        this->windowData.eventCallback = callback;
    }

    void VkWindow::setVSync(bool enable)
    {
        if (enable)
        {
            glfwSwapInterval(1);
        }
        else
        {
            glfwSwapInterval(0);
        }
    }

    bool VkWindow::isVSync() const
    {
        return true;
    }

    void* VkWindow::getNativeWindow()
    {
        return static_cast<void*> (window);
    }
}
