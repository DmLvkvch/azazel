#pragma once

#include "Texture.h"
#include "FrameBufferTarget.h"

namespace Azazel
{
	class FrameBuffer
	{
	private:
		unsigned int rendererId;
	public:
		Texture* texture;
		FrameBufferTarget* frameBufferDepthTarget;
		FrameBuffer();
		~FrameBuffer();
		void bind();
		void unbind();
		void setTextureTarget(Texture* texture);
		void setFrameBufferDepthTarget(FrameBufferTarget* frameBufferTarget);
	};
}