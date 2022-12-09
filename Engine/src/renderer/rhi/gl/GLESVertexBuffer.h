#pragma once

#include <renderer/VertexBuffer.h>

namespace Azazel
{
	class GLESVertexBuffer : public VertexBuffer
	{
	private:
		unsigned int rendererId;
	public:
		GLESVertexBuffer(const void* data, int size);
		~GLESVertexBuffer();
		void bind() const;
		void unbind() const;
	};
}