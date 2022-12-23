#pragma once

#include "Texture.h"

#include "FrameBufferTarget.h"

namespace Azazel
{
	class FrameBuffer
	{
	public:
        FrameBuffer() = default;
		virtual ~FrameBuffer();
		virtual void bind() const = 0;
		virtual void unbind() const = 0;
		virtual void setDepthTarget(FrameBufferTarget* frameBufferTarget) = 0;
		virtual void addColorAttachment(const Texture* texture, int slot = 0) = 0;
		static FrameBuffer* create(Texture* texture, FrameBufferTarget* frameBufferTarget);
	};
}