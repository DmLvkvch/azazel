#pragma once

class FrameBufferTarget
{
    FrameBufferTarget();
    virtual ~FrameBufferTarget();

    virtual int getWidth();
    virtual int getHeight();
    virtual bool isTextureTarget();
};