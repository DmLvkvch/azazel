#pragma once

#include "GLESVertexBufferLayout.h"
#include <renderer/VertexArray.h>
#include <renderer/VertexBuffer.h>
#include <renderer/VertexBufferLayout.h>

namespace Azazel
{
	class GLESVertexArray : public VertexArray
	{
	private:
		unsigned int rendererId;
	public:
		GLESVertexArray();
		~GLESVertexArray();
		void addBuffer(VertexBuffer& vb, const GLESVertexBufferLayout& layout, int attribOffset = 0);
		void bind() const;
		void unbind() const;
	};
}