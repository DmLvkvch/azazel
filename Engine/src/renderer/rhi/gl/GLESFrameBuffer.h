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
	public:
		std::vector<TextureRHI*> colorAttachments;
		FrameBufferTarget* frameBufferDepthTarget;
		GLESFrameBuffer(const std::vector<TextureRHI*>& colorAttachments);
		GLESFrameBuffer(TextureRHI* texture);
		~GLESFrameBuffer();
		void bind();
		void unbind();
		void setColorTargets(const std::vector<TextureRHI*>& colorAttachments);
		void setTextureTarget(TextureRHI* texture, int slot = 0);
		void setFrameBufferDepthTarget(FrameBufferTarget* frameBufferTarget);
	};
}