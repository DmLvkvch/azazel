#pragma once

#include "ColorFormat.h"

#include "renderer/rhi/TextureRHI.h"

namespace Azazel
{
    class Texture
    {
    private:
        unsigned char* data;
        int width;
        int height;
        ColorFormat colorFormat;
        TextureRHI* textureRHI;

    public:

        enum TextureFilter
        {
            LINEAR,
            NEAREST
        };

        enum TextureWrap
        {
            REPEAT,
            MIRRORED_REPEAT,
            CLAMP_TO_EDGE,
            CLAMP_TO_BORDER
        };
        
        Texture(int width, int height, const char* data);

        ~Texture();
    
        int getWidth();

        int getHeight();

        ColorFormat getColorFormat();

        TextureRHI* getTextureRHI();
    };
}