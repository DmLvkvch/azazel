#pragma once

#include <renderer/rhi/IndexBufferRHI.h>

namespace Azazel
{
	class GLESIndexBuffer : public IndexBufferRHI
	{
	private:
		unsigned int rendererId;
		int count;

	public:
		GLESIndexBuffer(const void* data, int size);

		~GLESIndexBuffer();

		void bind() override;

		void unbind() override;

		int getElementCount() override;
	};
}