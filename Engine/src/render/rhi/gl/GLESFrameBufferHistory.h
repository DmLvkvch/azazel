#pragma once

#include <vector>

namespace Azazel
{
    class GLESFrameBuffer;

    class FrameBufferHistory
    {
    public:
        std::vector<unsigned int> frameBufferStack {0};

        void activate(unsigned int id);
        void deactivateLast();
    };
}