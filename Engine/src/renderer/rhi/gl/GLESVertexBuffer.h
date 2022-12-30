#pragma once

#include <renderer/VertexBuffer.h>

namespace Azazel
{
	class GLESVertexBuffer : public VertexBuffer
	{
	private:
		unsigned int rendererId;
		BufferLayout bufferLayout;
	public:
		GLESVertexBuffer(const void* data, size_t size);
		~GLESVertexBuffer();
		void bind() const override;
		void unbind() const override;
        virtual void setLayout(const BufferLayout& bufferlayout) override;
        virtual const BufferLayout& getBufferlayout() const override;
	};
}