#pragma once

namespace Azazel
{
	class TextureRHI
	{
	public:

		virtual ~TextureRHI();

		virtual int getWidth();

		virtual int getHeight();

		virtual void bind() = 0;
		
		virtual void unbind() = 0;

		unsigned int getRendererId();
	};
}