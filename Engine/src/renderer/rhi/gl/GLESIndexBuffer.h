#pragma once

#include <renderer/IndexBuffer.h>

namespace Azazel
{
	class GLESIndexBuffer : public IndexBuffer
	{
	private:
		unsigned int rendererId;
		int count;

	public:
		GLESIndexBuffer(const void* data, int count);

		~GLESIndexBuffer();

		void bind() const override;

		void unbind() const override;

		int getElementCount() const override;
	};
}