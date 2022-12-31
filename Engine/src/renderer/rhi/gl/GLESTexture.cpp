#include "GLESTexture.h"

#include "gl_headers.h"

#include <stb_image/stb_image.h>

#include <iostream>

namespace Azazel
{
    GLESTexture::GLESTexture(const TextureData& textureData)
    :width(textureData.width), height(textureData.height), bpp(textureData.bpp)
    {
        createTexture(textureData.data, width, height, bpp);
    }

    GLESTexture::GLESTexture(const unsigned char* data, int width, int height, int bpp)
        :width(width), height(height), bpp(bpp)
    {
        createTexture(data, width, height, bpp);
    }

    GLESTexture::GLESTexture(int width, int height, int color)
    {
        unsigned char* data = new unsigned char[width * height * 4];
        unsigned char b = color & 0xff;
        unsigned char g = (color >> 8) & 0xff;
        unsigned char r = (color >> 16) & 0xff;
        unsigned char a = (color >> 24) & 0xff;
        for (int i = 0; i < width * height * 4; i += 4)
        {
            data[i + 0] = r;
            data[i + 1] = g;
            data[i + 2] = g;
            data[i + 3] = a;
        }
        createTexture(data, width, height, 4);
    }

    void GLESTexture::createTexture(const unsigned char* data, int width, int height, int bpp)
    {
        glGenTextures(1, &rendererId);
        bind();
        this->width = width;
        this->height = height;
        this->bpp = bpp;
        setTextureFilter(Texture::NEAREST);
        setTextureWrap(Texture::REPEAT);
        if (data)
        {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        }
        else
        {
            std::cout << "Failed to load texture" << std::endl;
        }
        delete[] data;
        unbind();
    }

    GLESTexture::~GLESTexture()
    {
        glDeleteTextures(1, &rendererId);
    }

    void GLESTexture::bind(unsigned int slot) const
    {
        glActiveTexture(GL_TEXTURE0 + slot);
        glBindTexture(GL_TEXTURE_2D, rendererId);
    }

    void GLESTexture::unbind() const
    {
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    unsigned int GLESTexture::textureFilterToGLFormat (Texture::TextureFilter textureFilter)
    {
        switch (textureFilter)
        {
            case Texture::LINEAR:
            {
                return GL_LINEAR;
            }
            case Texture::NEAREST:
            {
                return GL_NEAREST;
            }
        }
        return 0;
    }


    unsigned int GLESTexture::textureWrapToGLFormat (Texture::TextureWrap textureWrap)
    {
        switch (textureWrap)
        {
            case Texture::REPEAT:
            {
                return GL_REPEAT;
            }
            case Texture::MIRRORED_REPEAT:
            {
                return GL_MIRRORED_REPEAT;
            }
            case Texture::CLAMP_TO_EDGE:
            {
                return GL_CLAMP_TO_EDGE;
            }
            case Texture::CLAMP_TO_BORDER:
            {
                return GL_CLAMP_TO_BORDER;
            }
        }
        return 0;
    }

    void GLESTexture::setTextureFilter(Texture::TextureFilter textureFilter)
    {
        this->textureFilter = textureFilter;
        unsigned int  filter = textureFilterToGLFormat(textureFilter);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filter);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filter);
    }

    void GLESTexture::setTextureWrap(Texture::TextureWrap textureWrap)
    {
        this->textureWrap = textureWrap;
        unsigned int wrap = textureWrapToGLFormat(textureWrap);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrap);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrap);
    }

    unsigned int GLESTexture::getRendererId() const
    {
        return rendererId;
    }
}