#pragma once

namespace Azazel
{
	class GLESVertexBuffer
	{
	public:
		unsigned int rendererId;

		GLESVertexBuffer(const void* data, int size);

		~GLESVertexBuffer();

		void bind() const;
		void unbind() const;
	};
}