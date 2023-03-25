#include "GLESCubeMap.h"

#include "gl_headers.h"
#include <stb_image/stb_image.h>
#include <iostream>
#include <vector>
#include <string>

#include "logging/Log.h"

namespace Azazel
{
    GLESCubeMap::GLESCubeMap(std::array<TextureData, 6> textures)
    {
        glGenTextures(1, &textureID);
        glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);
        
        for (unsigned int i = 0; i < 6; i++)
        {
            auto& data = textures[i];
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, data.width, data.height, 0, GL_RGB, GL_UNSIGNED_BYTE, data.data);
        }
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    }

    GLESCubeMap::~GLESCubeMap()
    {
        glDeleteTextures(1, &textureID);
    }

    void GLESCubeMap::bind()
    {

    }

    void GLESCubeMap::unbind()
    {

    }
}