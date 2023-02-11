#include "GLESTexture.h"

#include "gl_headers.h"
#include <iostream>

namespace Azazel
{
    GLESTexture::GLESTexture(const TextureData& textureData)
    : Texture(textureData.width, textureData.height, textureData.bpp, textureData.data, Format::RGBA32)
    {
        createTexture(getWidth(), getHeight(), getBpp(), textureData.data);
    }

    GLESTexture::GLESTexture(int width, int height, int bpp, const unsigned char* data)
    : Texture(width, height, bpp, data, Format::RGBA32)
    {
        createTexture(width, height, bpp, data);
    }

    GLESTexture::GLESTexture(int width, int height, int color)
    {
        unsigned char* data = new unsigned char[width * height * 4];
        unsigned char b = (color >> 0 ) & 0xff;
        unsigned char g = (color >> 8 ) & 0xff;
        unsigned char r = (color >> 16) & 0xff;
        unsigned char a = (color >> 24) & 0xff;
        for (int i = 0; i < width * height * 4; i += 4)
        {
            data[i + 0] = r;
            data[i + 1] = g;
            data[i + 2] = b;
            data[i + 3] = a;
        }
        createTexture(width, height, 4, data);
    }

    void GLESTexture::createTexture(int width, int height, int bpp, const unsigned char* data)
    {
        glGenTextures(1, &rendererID);
        bind();
        setTextureFilter(Texture::Nearest);
        setTextureWrap(Texture::Repeat);

        int format = 0;
        int internalFormat = 0;
        if (bpp == 3)
        {
            format = GL_RGB;
            internalFormat = GL_RGB8;
            glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
        }
        else
        {
            format = GL_RGBA;
            internalFormat = GL_RGBA8;
        }
        if (!data)
        {
            std::cout<<"Warning. Creating texture with no data provided"<<std::endl;
        }
        
        glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        if (data)
        {
            delete[] data;
            data = nullptr;
        }
        unbind();
    }

    GLESTexture::~GLESTexture()
    {
        glDeleteTextures(1, &rendererID);
    }

    void GLESTexture::bind(unsigned int slot) const
    {
        glActiveTexture(GL_TEXTURE0 + slot);
        glBindTexture(GL_TEXTURE_2D, rendererID);
    }

    void GLESTexture::unbind() const
    {
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    unsigned int GLESTexture::textureFilterToGLFormat (Texture::TextureFilter textureFilter)
    {
        switch (textureFilter)
        {
            case Texture::Linear:
            {
                return GL_LINEAR;
            }
            case Texture::Nearest:
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
            case Texture::Repeat:
            {
                return GL_REPEAT;
            }
            case Texture::MirroredRepeat:
            {
                return GL_MIRRORED_REPEAT;
            }
            case Texture::ClampToEdge:
            {
                return GL_CLAMP_TO_EDGE;
            }
            case Texture::ClampToBorder:
            {
                return GL_CLAMP_TO_BORDER;
            }
        }
        return 0;
    }

    void GLESTexture::setTextureFilter(Texture::TextureFilter textureFilter)
    {
        unsigned int filter = textureFilterToGLFormat(textureFilter);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filter);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filter);
    }

    void GLESTexture::setTextureWrap(Texture::TextureWrap textureWrap)
    {
        unsigned int wrap = textureWrapToGLFormat(textureWrap);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrap);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrap);
    }

    unsigned int GLESTexture::getRendererId() const
    {
        return rendererID;
    }
}