#pragma once

namespace Azazel
{
	class GLESIndexBuffer
	{
	private:
		unsigned int rendererId;

		int count;
	public:
		GLESIndexBuffer(const void* data, int size);

		~GLESIndexBuffer();

		void bind() const;

		void unbind() const;

		int getCount() const;
	};
}