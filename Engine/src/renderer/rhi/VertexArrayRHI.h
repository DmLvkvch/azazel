#pragma once

#include "VertexBufferLayout.h"
#include "VertexBufferRHI.h"

namespace Azazel
{
	class VertexArrayRHI
	{
	public:
		virtual ~VertexArrayRHI();
		virtual void bind() = 0;
		virtual void unbind() = 0;
		virtual void addBuffer(VertexBufferRHI& vertexBufferRHI, const VertexBufferLayout& layout, int attribOffset = 0) = 0;
	};
}