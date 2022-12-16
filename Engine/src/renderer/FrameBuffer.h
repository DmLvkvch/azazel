#pragma once

namespace Azazel
{
	class FrameBuffer
	{
	public:
        FrameBuffer() = default;
		virtual ~FrameBuffer();
		virtual void bind() const = 0;
		virtual void unbind() const = 0;
	};
}