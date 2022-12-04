#pragma once

#include "VertexBufferLayout.h"
#include "VertexBufferRHI.h"
#include "gl/GLESVertexBufferLayout.h"

namespace Azazel
{
	class VertexArrayRHI
	{
	public:
		virtual ~VertexArrayRHI();
		virtual void bind() = 0;
		virtual void unbind() = 0;
		virtual void addBuffer(VertexBufferRHI& vertexBufferRHI, const GLESVertexBufferLayout& layout, int attribOffset = 0) = 0;
	};
}