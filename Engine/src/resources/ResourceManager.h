#pragma once

#include <unordered_map>
#include <string>
#include <memory>
#include "LRUCache.h"
#include "render/Shader.h"
#include "render/Texture.h"

namespace Azazel
{
    template <typename T>
    class ResourceManager
    {
    public:
        ResourceManager()
        {

        }

        virtual T loadResource(const std::string& path, bool needCache = true) = 0;
    protected:
        void cacheResource(std::string key, const T& resource)
        {
            lruCache.put(key, resource);
        }
    private:
        std::unordered_map<std::string, T> resources;   
        LRUCache<std::string, T> lruCache;
    };

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