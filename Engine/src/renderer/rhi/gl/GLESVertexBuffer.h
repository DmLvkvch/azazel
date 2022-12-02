#pragma once

#include <renderer/rhi/VertexBufferRHI.h>

namespace Azazel
{
	class GLESVertexBuffer : public VertexBufferRHI
	{
	private:
		unsigned int rendererId;
	public:
		GLESVertexBuffer(const void* data, int size);
		~GLESVertexBuffer();
		void bind();
		void unbind();
	};
}