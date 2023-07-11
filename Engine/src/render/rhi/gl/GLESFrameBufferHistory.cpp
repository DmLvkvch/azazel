#include "GLESFrameBuffer.h"
#include "gl_headers.h"

namespace Azazel
{
    void FrameBufferHistory::activate(unsigned int id)
    {
        this->frameBufferStack.push_back(id);
        glBindFramebuffer(GL_FRAMEBUFFER, id);
    }

    void FrameBufferHistory::deactivateLast()
    {
        this->frameBufferStack.pop_back();
        glBindFramebuffer(GL_FRAMEBUFFER, frameBufferStack.back());
    }
}