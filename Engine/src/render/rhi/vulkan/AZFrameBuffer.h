#pragma once

#include "render/FrameBuffer.h"

namespace Azazel
{
    class AZFrameBuffer
    {
    public:
        AZFrameBuffer(Texture* texture);
        AZFrameBuffer(Texture* texture, FrameBufferTarget* depthTarget);
        AZFrameBuffer(Texture* texture, Texture* depthTarget){}

        ~AZFrameBuffer();
    private:
        unsigned int rendererID;
    };
}