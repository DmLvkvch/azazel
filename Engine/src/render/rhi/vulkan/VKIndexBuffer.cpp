#include "VKIndexBuffer.h"

#include "vk_headers.h"

namespace Azazel
{
    VKIndexBuffer::VKIndexBuffer(const void* data, size_t count)
    {
        this->count = count;

    }

    VKIndexBuffer::~VKIndexBuffer()
    {
    }

    void VKIndexBuffer::bind() const
    {
    }

    void VKIndexBuffer::unbind() const
    {
    }

    size_t VKIndexBuffer::getElementCount() const
    {
        return count;
    }
}