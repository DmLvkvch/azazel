#include "VKVertexBuffer.h"

#include "vk_headers.h"

namespace Azazel
{
    VKVertexBuffer::VKVertexBuffer(const void* data, size_t size)
    {
        
    }

    VKVertexBuffer::~VKVertexBuffer()
    {
    }

    void VKVertexBuffer::bind() const
    {
    }

    void VKVertexBuffer::unbind() const
    {
    }

    void VKVertexBuffer::updateSubData(int offset, void* data, int size)
    {
    }

    void VKVertexBuffer::setLayout(const BufferLayout& bufferLayout)
    {
         this->bufferLayout = bufferLayout;
    }

    const BufferLayout& VKVertexBuffer::getBufferLayout() const
    {
        return bufferLayout;
    }
}