#pragma once

namespace Azazel
{
	class VertexBufferRHI
	{
	public:
		virtual ~VertexBufferRHI();
		virtual void bind() = 0;
		virtual void unbind() = 0;
	};
}