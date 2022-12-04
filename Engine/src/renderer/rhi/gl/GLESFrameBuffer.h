#pragma once

#include <vector>

#include <renderer/rhi/FrameBufferRHI.h>
#include <renderer/rhi/TextureRHI.h>
#include "GLESFrameBufferTarget.h"

namespace Azazel
{
	class GLESFrameBuffer : public FrameBufferRHI
	{
	private:
		unsigned int rendererId;
		std::vector<TextureRHI*> colorAttachments;
		FrameBufferTarget* frameBufferDepthTarget;
	public:

		GLESFrameBuffer(const std::vector<TextureRHI*>& colorAttachments);
		GLESFrameBuffer(TextureRHI* texture);
		~GLESFrameBuffer();
		void bind() override;
		void unbind() override;
		void setTextureTarget(TextureRHI* texture, int slot = 0);
		void setFrameBufferDepthTarget(FrameBufferTarget* frameBufferTarget);
		void addColorAttachment(TextureRHI* textureRHI);
	};
}