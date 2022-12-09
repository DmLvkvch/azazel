#pragma once

#include <vector>

#include <renderer/FrameBuffer.h>
#include <renderer/Texture.h>
#include "GLESFrameBufferTarget.h"

namespace Azazel
{
	class GLESFrameBuffer : public FrameBuffer
	{
	private:
		unsigned int rendererId;
		std::vector<Texture*> colorAttachments;
		FrameBufferTarget* frameBufferDepthTarget;
	public:

		GLESFrameBuffer(const std::vector<Texture*>& colorAttachments);
		GLESFrameBuffer(Texture* texture);
		~GLESFrameBuffer();
		void bind() const override;
		void unbind() const override;
		void setTextureTarget(Texture* texture, int slot = 0);
		void setFrameBufferDepthTarget(FrameBufferTarget* frameBufferTarget);
		void addColorAttachment(Texture* texture);
	};
}