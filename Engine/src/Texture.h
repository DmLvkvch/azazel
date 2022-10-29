#pragma once

#include <string>

namespace Azazel
{
	enum TextureFilter
	{
		LINEAR,
		NEAREST		
	};

	enum TextureWrap
	{
		REPEAT,
		MIRRORED_REPEAT,
		CLAMP_TO_EDGE,
		CLAMP_TO_BORDER		
	};

	class Texture
	{
	private:
		unsigned int rendererId;
		unsigned char* textureData;
		int width;
		int height;
		int bpp;

		TextureFilter textureFilter;
		TextureWrap textureWrap;

		unsigned int  textureFilterToGLFormat(TextureFilter textureFilter);
		unsigned int  textureWrapToGLFormat(TextureWrap textureWrap);

	public:
		void createTexture(unsigned char* data, int width, int height, int bpp);
		Texture(std::string path);
		Texture();
		Texture(unsigned char* data, int width, int height, int bpp);
		~Texture();
		void bind(unsigned int slot = 0);
		void unbind();

		void setTextureFilter(TextureFilter textureFilter);
		void setTextureWrap(TextureWrap textureWrap);

		int getWidth() const
		{
			return width;
		}

		int getHeight() const
		{
			return height;
		}
	};
}