#pragma once

#include "VertexBufferLayout.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"

namespace Azazel
{
	class VertexArray
	{
	public:
		virtual ~VertexArray() {}
		virtual void bind() const = 0;
		virtual void unbind() const = 0;
		virtual void addBuffer(VertexBuffer& vertexBuffer, VertexBufferLayout* layout, int attribOffset = 0) = 0;
	};
}