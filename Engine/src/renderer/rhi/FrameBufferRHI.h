#pragma once

namespace Azazel
{
	class FrameBufferRHI
	{
	public:
		virtual ~FrameBufferRHI();
		virtual void bind() = 0;
		virtual void unbind() = 0;
	};
}