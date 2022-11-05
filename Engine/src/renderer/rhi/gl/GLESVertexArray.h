#pragma once

#include "GLESVertexBuffer.h"
#include "GLESVertexBufferLayout.h"

namespace Azazel
{
	class GLESVertexArray
	{
	private:
		unsigned int rendererId;
	public:

		GLESVertexArray();
		
		~GLESVertexArray();

		void addBuffer(GLESVertexBuffer& vb, const GLESVertexBufferLayout& layout, int attribOffset = 0);

		void bind() const;

		void unbind() const;
	};
}