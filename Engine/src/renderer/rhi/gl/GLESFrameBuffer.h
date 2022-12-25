#pragma once

#include <vector>

#include <renderer/FrameBuffer.h>
#include <renderer/Texture.h>
#include <renderer/FrameBufferTarget.h>

namespace Azazel
{
	class GLESFrameBuffer : public FrameBuffer
	{
	private:
		unsigned int rendererId;
		std::vector<Texture*> colorAttachments;
		FrameBufferTarget* frameBufferDepthTarget;
	public:

		GLESFrameBuffer(std::shared_ptr<Texture> texture);
		GLESFrameBuffer(Texture* texture, FrameBufferTarget* frameBufferTarget);
		~GLESFrameBuffer();
		void bind() const override;
		void unbind() const override;
		void setDepthTarget(FrameBufferTarget* frameBufferTarget) override;
		void addColorAttachment(const Texture* texture, int slot = 0) override;
	};
}