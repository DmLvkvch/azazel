#include "Texture.h"

#include "gl_headers.h"

#include <stb_image/stb_image.h>

#include <iostream>

namespace Azazel
{
    Texture::Texture(std::string path)
    {

    stbi_set_flip_vertically_on_load(true);
    unsigned char* data = stbi_load(path.c_str(), &width, &height, &bpp, 4);
    
    createTexture(data, width, height, bpp);
    stbi_image_free(data);
    }

    Texture::Texture(unsigned char* data, int width, int height, int bpp)
        :width(width), height(height), bpp(bpp)
    {
        createTexture(data, width, height, bpp);
    }

    Texture::Texture(int color)
    {
        unsigned char *data = new unsigned char[1024 * 1024 * 4];
        unsigned char b = color & 0xff;
        unsigned char g = (color >> 8) & 0xff;
        unsigned char r = (color >> 16) & 0xff;
        unsigned char a = (color >> 24) & 0xff;
        for (int i = 0; i < 1024 * 1024 * 4; i+=4)
        {
            data[i] = r;
            data[i + 1] = g;
            data[i + 2] = b;
            data[i + 3] = a;
        }
        createTexture(data, 1024, 1024, 4);
        delete[] data;
    }

    void Texture::createTexture(unsigned char* data, int width, int height, int bpp)
    {
        glGenTextures(1, &rendererId);
        glBindTexture(GL_TEXTURE_2D, rendererId);
        this->width = width;
        this->height = height;
        this->bpp = bpp;

        setTextureFilter(NEAREST);
        setTextureWrap(REPEAT);

        if (data)
        {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        }
        else
        {
            std::cout << "Failed to load texture" << std::endl;
        }
    }

    Texture::~Texture()
    {
        glDeleteTextures(1, &rendererId);
    }

    void Texture::bind(unsigned int slot)
    {
        glActiveTexture(GL_TEXTURE0 + slot);
        glBindTexture(GL_TEXTURE_2D, rendererId);
    }

    void Texture::unbind()
    {
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    unsigned int Texture::textureFilterToGLFormat (TextureFilter textureFilter)
    {
        switch (textureFilter)
        {
            case LINEAR:
            {
                return GL_LINEAR;
            }
            case NEAREST:
            {
                return GL_NEAREST;
            }
        }
        return 0;
    }


    unsigned int Texture::textureWrapToGLFormat (TextureWrap textureWrap)
    {
        switch (textureWrap)
        {
            case REPEAT:
            {
                return GL_REPEAT;
            }
            case MIRRORED_REPEAT:
            {
                return GL_MIRRORED_REPEAT;
            }
            case CLAMP_TO_EDGE:
            {
                return GL_CLAMP_TO_EDGE;
            }
            case CLAMP_TO_BORDER:
            {
                return GL_CLAMP_TO_BORDER;
            }
        }
        return 0;
    }

    void Texture::setTextureFilter(TextureFilter textureFilter)
    {
        this->textureFilter = textureFilter;
        unsigned int  filter = textureFilterToGLFormat(textureFilter);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filter);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filter);
    }

    void Texture::setTextureWrap(TextureWrap textureWrap)
    {
        this->textureWrap = textureWrap;
        unsigned int wrap = textureWrapToGLFormat(textureWrap);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrap);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrap);
    }
}