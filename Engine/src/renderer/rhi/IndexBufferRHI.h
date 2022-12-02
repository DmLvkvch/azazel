#pragma once

namespace Azazel
{
	class IndexBufferRHI
	{
	public:
		IndexBufferRHI();
		virtual ~IndexBufferRHI();
		virtual void bind() = 0;
		virtual void unbind() = 0;
		virtual int getElementCount() = 0;
	};
}