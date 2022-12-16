#pragma once

#include <stb_image/stb_image.h>

#include "renderer/TextureData.h"

namespace Azazel
{
    class TextureUtils
    {
    public:
        static TextureData loadTexture(std::string path, bool flipVertically = true)
        {
            stbi_set_flip_vertically_on_load(flipVertically);
            int width;
            int height;
            int bpp;
            unsigned char* data = stbi_load(path.c_str(), &width, &height, &bpp, 0);
            TextureData textureData(width, height, bpp, data);
            return textureData;
    
        }
    };
}