#include "GLESCubeMap.h"

#include "gl_headers.h"
#include "logging/Log.h"

#include <stb_image/stb_image.h>
#include <iostream>
#include <vector>
#include <string>

namespace Azazel
{
    GLESCubeMap::GLESCubeMap(std::array<TextureData, 6> textures)
    {
        glGenTextures(1, &textureID);
        bind();
        static const unsigned int types[6] = {  GL_TEXTURE_CUBE_MAP_POSITIVE_X,
                                                GL_TEXTURE_CUBE_MAP_NEGATIVE_X,
                                                GL_TEXTURE_CUBE_MAP_POSITIVE_Y,
                                                GL_TEXTURE_CUBE_MAP_NEGATIVE_Y,
                                                GL_TEXTURE_CUBE_MAP_POSITIVE_Z,
                                                GL_TEXTURE_CUBE_MAP_NEGATIVE_Z 
                                            };
        for (unsigned int i = 0; i < 6; i++)
        {
            auto& data = textures[i];
            int format = 0;
            int internalFormat = 0;
            int bpp = data.bpp;
            if (bpp == 3)
            {
                format = GL_RGB;
                internalFormat = GL_RGB8;
                glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
            }
            else if (bpp == 1)
            {
                format = GL_RED;
                internalFormat = GL_RED;
                glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
            }
            else
            {
                format = GL_RGBA;
                internalFormat = GL_RGBA8;
            }
            glTexImage2D(types[i], 0, internalFormat, data.width, data.height, 0, format, GL_UNSIGNED_BYTE, data.data);
        }
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
        unbind();
    }

    GLESCubeMap::~GLESCubeMap()
    {
        glDeleteTextures(1, &textureID);
    }

    void GLESCubeMap::bind(int slot) const
    {
        glActiveTexture(GL_TEXTURE0 + slot);
        glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);
    }

    void GLESCubeMap::unbind() const
    {
        glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
    }
}