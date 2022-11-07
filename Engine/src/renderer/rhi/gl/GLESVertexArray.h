#pragma once

#include <renderer/rhi/VertexArrayRHI.h>
#include <renderer/rhi/VertexBufferRHI.h>
#include "GLESVertexBufferLayout.h"

namespace Azazel
{
	class GLESVertexArray : public VertexArrayRHI
	{
	private:
		unsigned int rendererId;
	public:

		GLESVertexArray();
		
		~GLESVertexArray();

		void addBuffer(VertexBufferRHI& vb, const GLESVertexBufferLayout& layout, int attribOffset = 0);

		void bind();

		void unbind();
	};
}