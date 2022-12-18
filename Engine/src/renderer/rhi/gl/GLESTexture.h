#pragma once

#include <string>
#include <renderer/Texture.h>

namespace Azazel
{
	class GLESTexture : public Texture
	{
	private:
		unsigned int rendererId;
		unsigned char* textureData;
		int width;
		int height;
		int bpp;
		Texture::TextureFilter textureFilter;
		Texture::TextureWrap textureWrap;
		unsigned int textureFilterToGLFormat(Texture::TextureFilter textureFilter);
		unsigned int textureWrapToGLFormat(Texture::TextureWrap textureWrap);
		void createTexture(const unsigned char* data, int width, int height, int bpp);
	public:
		GLESTexture (const TextureData& textureData);
		GLESTexture(int width, int height, int color);
		GLESTexture(const unsigned char* data, int width, int height, int bpp);
		~GLESTexture();
		void bind(unsigned int slot = 0) const;
		void unbind() const;
		void setTextureFilter(Texture::TextureFilter textureFilter);
		void setTextureWrap(Texture::TextureWrap textureWrap);
		unsigned int getRendererId();
	};
}