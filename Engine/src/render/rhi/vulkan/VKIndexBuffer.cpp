#include "VKIndexBuffer.h"

#include "vk_headers.h"

namespace Azazel
{
    VKIndexBuffer::VKIndexBuffer(const void* data, unsigned int count)
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

    unsigned int VKIndexBuffer::getElementCount() const
    {
        return count;
    }
}