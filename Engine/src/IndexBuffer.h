#pragma once

namespace Azazel
{
	class IndexBuffer
	{
	public:

		unsigned int rendererId;

		int count;

		IndexBuffer(const void* data, int size);

		~IndexBuffer();

		void bind() const;

		void unbind() const;

		int getCount() const;
	};
}