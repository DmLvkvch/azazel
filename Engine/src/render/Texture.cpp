#include "Texture.h"

#ifdef AZAZEL_GL
#include "rhi/gl/GLESTexture.h"
#include "rhi/gl/GLESDepthTexture.h"
#include "render/rhi/gl/GLESCubeMap.h"
#else
#include "rhi/vulkan/AZTexture.h"
#endif

namespace Azazel
{
    Texture::Texture(int width, int height, int bpp, const unsigned char* data, Format format)
    : width(width), height(height), bpp(bpp), data(data)
    {
    }

    Texture::Texture(const TextureData& textureData)
    {
    }
    
    Texture::~Texture()
    {
    }

    void Texture::setLabel(const std::string& label)
    {
        this->label = label;
    }


    Texture* Texture::create(const TextureData& textureData)
    {
        #ifdef AZAZEL_GL
        return new GLESTexture(textureData);
        #else 
        return new VKTexture(textureData);
        #endif
    }

    Texture* Texture::create(int width, int height, int color)
    {
        #ifdef AZAZEL_GL
        return new GLESTexture(width, height, color);
        #else
        return nullptr;
        #endif
    }

    Texture* Texture::createDepthTexture(const TextureData& textureData)
    {
        #ifdef AZAZEL_GL
        return new GLESDepthTexture(textureData);
        #else
        return nullptr;
        #endif
    }

    Texture* Texture::createDepthTexture(int width, int height)
    {
        TextureData textureData(width, height, 4, nullptr);
        #ifdef AZAZEL_GL
        return new GLESDepthTexture(textureData);
        #else
        return nullptr;
        #endif
    }

    CubeMap::CubeMap()
    {
    }

    CubeMap::~CubeMap()
    {
    }
    
    CubeMap* CubeMap::create(std::array<TextureData, 6> textures)
    {
        return nullptr;
    }
}