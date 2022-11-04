#pragma once

#include "VertexBuffer.h"
#include "VertexBufferLayout.h"

namespace Azazel
{
	class VertexArray
	{
	private:
		unsigned int rendererId;
	public:

		VertexArray();
		
		~VertexArray();

		void addBuffer(VertexBuffer& vb, const VertexBufferLayout& layout, int attribOffset = 0);

		void bind() const;

		void unbind() const;
	};
}