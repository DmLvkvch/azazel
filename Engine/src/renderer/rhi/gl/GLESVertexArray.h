#pragma once

#include "GLESVertexBufferLayout.h"
#include <renderer/VertexArray.h>
#include <renderer/VertexBuffer.h>

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
		void addBuffer(VertexBuffer& vb, const BufferLayout& layout) override;
		void bind() const override;
		void unbind() const override;
	};
}