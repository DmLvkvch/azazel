#pragma once

namespace Azazel
{
	class VertexArrayRHI
	{
	public:
		virtual ~VertexArrayRHI();

		virtual void bind() = 0;
		virtual void unbind() = 0;
	};
}