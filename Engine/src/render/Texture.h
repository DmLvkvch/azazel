#pragma once

#include "TextureData.h"
#include <string>

namespace Azazel
{
    class Texture
    {
    public:

        enum TextureFilter
        {
            Linear = 0,
            Nearest
        };

        enum TextureWrap
        {
            Repeat = 0,
            MirroredRepeat,
            ClampToEdge,
            ClampToBorder
        };

        enum Type
        {
            COLOR_1D = 0,
            COLOR_2D,
            COLOR_3D,
            COLOR_RT,
            DEPTH,
            CUBEMAP
        };

        enum Format
        {
            R8 = 0,
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
            DEPTH16,
            DEPTH24,
            DEPTH32,
            DEPTH24_STENCIL8,
            DEPTH32F,
            STENCIL,
            DEPTH_STENCIL,
            SCREEN,
            BGRA8_UNORM,
            NONE
        };

        static bool isDepth(Format format)
        {
            switch(format)
            {
                case DEPTH16:
                case DEPTH24:
                case DEPTH32:
                case DEPTH24_STENCIL8:
                case DEPTH32F:
                case DEPTH_STENCIL:
                    return true;
                default:
                    return false;
            }
            return false;
        }

        static bool isDepthStencil(Format format)
        {
            switch(format)
            {
                case DEPTH24_STENCIL8:
                case DEPTH_STENCIL:
                    return true;
                default:
                    return false;
            }
            return false;
        }


        Texture() = default;
        
        Texture(int width, int height, int bpp, const unsigned char* data, Format format);
        
        Texture(const TextureData& textureData);
        
        virtual ~Texture();
    
        const inline int getWidth() const
        {
            return width;
        }

        const inline int getHeight() const
        {
            return height;
        }

        const inline int getBpp() const
        {
            return bpp;
        }

        const inline Format getColorFormat() const
        {
            return format;
        }

        inline std::string getLabel() const
        {
            return label;
        }

        void setLabel(const std::string& label);

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
        const unsigned char* data;
        int bpp;
        int width;
        int height;
        TextureData textureData;
        std::string label = "DEFAULT_TEXTURE";
        Format format;
    };
}