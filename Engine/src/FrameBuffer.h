#pragma once

#include "Texture.h"

namespace Azazel
{
	class FrameBuffer
	{
	private:
		unsigned int rendererId;
	public:
		Texture* texture;
		FrameBuffer();
		~FrameBuffer();
		void bind();
		void unbind();
	};
}