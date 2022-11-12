#pragma once

namespace Azazel
{
	class TextureRHI
	{
	public:

		virtual ~TextureRHI();

		virtual int getWidth();

		virtual int getHeight();

		virtual void bind(unsigned int slot = 0) = 0;
		
		virtual void unbind() = 0;

		virtual unsigned int getRendererId() = 0;
	};
}