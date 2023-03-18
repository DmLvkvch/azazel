#pragma once

#include <stb_image/stb_image.h>
#include "render/TextureData.h"

namespace Azazel
{
    class TextureUtils
    {
    public:
        static TextureData loadTexture(std::string path, int desiredChannels = 0, bool flipVertically = true)
        {
            stbi_set_flip_vertically_on_load(flipVertically);
            int width = 0;
            int height = 0;
            int bpp = 0;
            unsigned char* data = stbi_load(path.c_str(), &width, &height, &bpp, desiredChannels);
            TextureData textureData(width, height, bpp, data);
            return textureData;
        }
    };
}