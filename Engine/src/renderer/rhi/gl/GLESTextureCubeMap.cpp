#include "GLESTextureCubeMap.h"

#include "renderer/rhi/gl/gl_headers.h"
#include "FileUtils.h"
#include <stb_image/stb_image.h>

namespace Azazel
{
    GLESTextureCubeMap::GLESTextureCubeMap(std::vector<std::string> textures)
    {
        glGenTextures(1, &rendererID);
        glBindTexture(GL_TEXTURE_CUBE_MAP, rendererID);
        int width, height, bpp;
        std::vector<std::string> faces
        {
            "images/skybox/right.jpg",
            "images/skybox/left.jpg",
            "images/skybox/top.jpg",
            "images/skybox/bottom.jpg",
            "images/skybox/front.jpg",
            "images/skybox/back.jpg"
        };
        
        stbi_set_flip_vertically_on_load(false);
        for (unsigned int i = 0; i < faces.size(); i++)
        {
            unsigned char *data = stbi_load(faces[i].c_str(), &width, &height, &bpp, 4);
            if (data)
            {
                glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
            }
            else
            {
                std::cout << "Cubemap tex failed to load at path: " << faces[i] << std::endl;
            }
            stbi_image_free(data);
        }
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    }

    GLESTextureCubeMap::~GLESTextureCubeMap()
    {

    }

    void GLESTextureCubeMap::bind(int slot)
    {
        glBindTexture(GL_TEXTURE_CUBE_MAP, rendererID);
    }

    void GLESTextureCubeMap::unbind()
    {
        glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
    }

}