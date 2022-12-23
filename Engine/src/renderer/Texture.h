#pragma once

#include "ColorFormat.h"
#include "TextureData.h"

namespace Azazel
{
    class Texture
    {
    private:
        unsigned char* data;
        int width;
        int height;
        ColorFormat colorFormat;
        TextureData textureData;
        std::string label = "DEFAULT_TEXTURE";
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

        Texture() = default;
        
		Texture(int width, int height, const unsigned char* data, ColorFormat colorFormat);
		
        Texture(const TextureData& textureData);
        
        virtual ~Texture();
    
        int getWidth();

        int getHeight();

        ColorFormat getColorFormat();
        virtual void bind(unsigned int slot = 0) const = 0;
        virtual void unbind() const = 0;

        virtual void setTextureFilter(Texture::TextureFilter textureFilter) = 0;
        virtual void setTextureWrap(Texture::TextureWrap textureWrap) = 0;
        virtual unsigned int getRendererId() const = 0;

        inline std::string getLabel() const
        {
            return label;
        }

        static Texture* create(const TextureData& textureData);
        static Texture* create(int width, int height, int color);

    };
}