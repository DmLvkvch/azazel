#pragma once

#include <renderer/rhi/gl/GLESVertexBufferLayout.h>
#include <renderer/rhi/VertexArrayRHI.h>
#include <renderer/rhi/VertexBufferRHI.h>
#include <renderer/rhi/VertexBufferLayout.h>

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