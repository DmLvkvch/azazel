#pragma once

namespace Azazel
{
    struct VirtualFrame
    {
        CommandBuffer commands{ vk::CommandBuffer{ } };
        StageBuffer stagingBuffer;
        vk::Fence commandQueueFence;
    };

    class VirtualFrameProvider
    {
        std::vector<VirtualFrame> virtualFrames;
        uint32_t presentImageIndex = 0;
        bool frameRunning = false;
        size_t currentFrame = 0;
    public:
        void init(size_t frameCount, size_t stageBufferSize);
        void destroy();

        void startFrame();
        VirtualFrame& getCurrentFrame();
        VirtualFrame& getNextFrame();
        const VirtualFrame& getCurrentFrame() const;
        const VirtualFrame& getNextFrame() const;
        uint32_t getPresentImageIndex() const;
        bool isFrameRunning() const;
        size_t getFrameCount() const;
        void endFrame();
    };
}