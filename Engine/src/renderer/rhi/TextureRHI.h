#pragma once

namespace Azazel
{
	class TextureRHI
	{
	public:

		TextureRHI();

		virtual ~TextureRHI();

		virtual int getWidth();

		virtual int getHeight();

		virtual void bind();
		
		virtual void unbind();

		unsigned int getRendererId();
	};
}