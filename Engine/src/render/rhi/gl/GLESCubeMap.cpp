#include "GLESCubeMap.h"

#include "gl_headers.h"
#include <stb_image/stb_image.h>
#include <iostream>
#include <vector>
#include <string>
#include "resources/ResourceManager.h"
#include "logging/Log.h"

namespace Azazel
{
    GLESCubeMap::GLESCubeMap()
    {
        glGenTextures(1, &textureID);
        glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);
        int width, height, bpp;
        std::vector<std::string> faces
        {
            "textures/skybox/right.jpg",
            "textures/skybox/left.jpg",
            "textures/skybox/top.jpg",
            "textures/skybox/bottom.jpg",
            "textures/skybox/front.jpg",
            "textures/skybox/back.jpg"
        };
        
        for (unsigned int i = 0; i < faces.size(); i++)
        {
            try
            {
                auto data = ResourceManagers::textureDataManager->loadResource(faces[i], 0, false);
                glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, data.width, data.height, 0, GL_RGB, GL_UNSIGNED_BYTE, data.data);
                delete[] data.data;
            }
            catch(...)
            {
                Log::getLogger()->errorLog("Could not load cube map texture" + faces[i]);
            }
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