#pragma once

#include "AbstractResourceManager.h"
#include "render/Texture.h"
#include "TextureUtils.h"

namespace Azazel
{
    class TextureResourceManager : public ResourceManager<std::string, Texture*>
    {
    public:
        TextureResourceManager()
        {
            std::cout << "TextureResourceManager constructor" << std::endl;
        }

        virtual ~TextureResourceManager()
        {
            std::cout << "TextureResourceManager destructor" << std::endl;
        }
        
        Texture* loadResource(const std::string& path, bool needCache = true)
        {
            if (needCache&& containsResource(path))
            {
                return getResource(path);
            }
            auto textureData = TextureUtils::loadTexture(path);
            auto texture = Texture::create(textureData);
            TextureUtils::freeTextureData(textureData);
            if (needCache)
            {
                cacheResource(path, texture);
            }
            return texture;
        }
    };

    class TextureDataResourceManager : public ResourceManager<std::string, TextureData>
    {
    public:

        TextureDataResourceManager()
        {
            std::cout << "TextureDataResourceManager constructor" << std::endl;
        }

        virtual ~TextureDataResourceManager()
        {
            std::cout << "TextureDataResourceManager destructor" << std::endl;
        }

        TextureData loadResource(const std::string& path, int flipVertically, bool needCache)
        {
            if (needCache && containsResource(path))
            {
                return getResource(path);
            }
            auto textureData = TextureUtils::loadTexture(path, flipVertically > 0);
            if (needCache)
            {
                cacheResource(path, textureData);
            }
            return textureData;
        }

        TextureData loadResource(const std::string& path, bool needCache = true)
        {
            return loadResource(path, 1, needCache);
        }
    };
}