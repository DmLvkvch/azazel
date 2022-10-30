#pragma once

namespace Azazel
{
	class IndexBuffer
	{
	private:
		unsigned int rendererId;

		int count;
	public:
		IndexBuffer(const void* data, int size);

		~IndexBuffer();

		void bind() const;

		void unbind() const;

		int getCount() const;
	};
}