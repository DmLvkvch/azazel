#pragma once

#include "gl_headers.h"

namespace Azazel
{
    class GLESCubeMap
    {
    public:
        GLESCubeMap()
        {
            unsigned int textureID;
            glGenTextures(1, &textureID);
            glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);
        }
    };
}