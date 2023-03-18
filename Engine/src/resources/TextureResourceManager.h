#pragma once

#include "ResourceManager.h"
#include "render/Texture.h"


namespace Azazel
{
    class TextureResourceManager : public ResourceManager<std::shared_ptr<Texture>>
    {
    public:
        std::shared_ptr<Texture> loadResource(const std::string& path, bool needCache = true)
        {
            return std::shared_ptr<Texture>();
        }
    private:
        static TextureResourceManager* textureManager;
    };

    class TextureDataResourceManager : public ResourceManager<std::shared_ptr<TextureData>>
    {
    public:
        std::shared_ptr<TextureData> loadResource(const std::string& path, bool needCache = true)
        {
            return std::shared_ptr<TextureData>();
        }
    private:
        static TextureDataResourceManager* textureDataManager;
    };
}