#pragma once

#include "ColorFormat.h"
#include "TextureData.h"

namespace Azazel
{
    class Texture
    {
    public:

        enum TextureFilter
        {
            Linear,
            Nearest
        };

        enum TextureWrap
        {
            Repeat,
            MirroredRepeat,
            ClampToEdge,
            ClampToBorder
        };

        enum class Type
        {
            COLOR_1D = 0,
            COLOR_2D,
            COLOR_3D,
            COLOR_RT,
            DEPTH,
            CUBEMAP
        };

        enum class Format
        {
            R8,
            R32_INT,
            R32_UINT,
            R32F,
            RG8,
            RGB8,
            RGBA8,
            RGB16,
            RGBA16,
            RGB32,
            RGBA32,
            RGBA32F,
            RGB,
            RGBA,
            DEPTH16_UNORM,
            DEPTH32F,
            STENCIL,
            DEPTH_STENCIL,
            SCREEN,
            BGRA8_UNORM,
            NONE
        };

        Texture() = default;
        
        Texture(int width, int height, const unsigned char* data, ColorFormat colorFormat);
        
        Texture(const TextureData& textureData);
        
        virtual ~Texture();
    
        int getWidth()
        {
            return width;
        }

        int getHeight()
        {
            return height;
        }

        Format getColorFormat()
        {
            return Format::RGBA32;
        }

        inline std::string getLabel() const
        {
            return label;
        }

        inline void setLabel(std::string label)
        {
            this->label = label;
        }

        // RENDER
        virtual void bind(unsigned int slot = 0) const = 0;
        virtual void unbind() const = 0;
        virtual void setTextureFilter(Texture::TextureFilter textureFilter) = 0;
        virtual void setTextureWrap(Texture::TextureWrap textureWrap) = 0;
        virtual unsigned int getRendererId() const = 0;

        // STATIC
        static Texture* create(const TextureData& textureData);
        static Texture* create(int width, int height, int color);
    private:
        unsigned char* data;
        int width;
        int height;
        ColorFormat colorFormat;
        TextureData textureData;
        std::string label = "DEFAULT_TEXTURE";
    };
}