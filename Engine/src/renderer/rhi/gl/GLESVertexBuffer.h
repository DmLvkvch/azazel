#pragma once

#include <renderer/rhi/VertexBufferRHI.h>

namespace Azazel
{
	class GLESVertexBuffer : public VertexBufferRHI
	{
	public:
		unsigned int rendererId;

		GLESVertexBuffer(const void* data, int size);

		~GLESVertexBuffer();

		void bind();
		void unbind();
	};
}