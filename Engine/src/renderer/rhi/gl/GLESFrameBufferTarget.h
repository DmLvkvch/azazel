#pragma once

namespace Azazel
{
    class FrameBufferTarget
    {
        FrameBufferTarget() = default;
        FrameBufferTarget(int width, int height, int color);
        virtual ~FrameBufferTarget();
        virtual int getWidth() = 0;
        virtual int getHeight() = 0;
        virtual bool isTextureTarget() = 0;
    };
}