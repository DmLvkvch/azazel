#pragma once

#include <string>

class Texture
{
private:
	unsigned int rendererId;
	unsigned char* textureData;
	int width;
	int height;
	int bpp;
public:
	Texture(std::string path);
	~Texture();
	void bind(unsigned int slot = 0);
	void unbind();
};