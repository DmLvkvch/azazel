#pragma once

#include "rhi/gl/GLESVertexBufferLayout.h"
#include "VertexBuffer.h"

namespace Azazel
{
	class VertexArray
	{
	public:
		virtual ~VertexArray() {}
		virtual void bind() const = 0;
		virtual void unbind() const = 0;
		virtual void addBuffer(VertexBuffer& vertexBuffer, const BufferLayout& layout) = 0;

		static VertexArray* create();
	};
}