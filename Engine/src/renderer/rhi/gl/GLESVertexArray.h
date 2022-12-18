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
		int lastIndex;
	public:
		GLESVertexArray();
		~GLESVertexArray();
		void addBuffer(VertexBuffer& vb, const GLESVertexBufferLayout& layout);
		void bind() const;
		void unbind() const;
	};
}