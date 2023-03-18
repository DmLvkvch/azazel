#pragma once

#include <unordered_map>
#include <string>
#include <memory>
#include "LRUCache.h"

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
}