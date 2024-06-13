#pragma once

#include <unordered_map>
#include <string>
#include <memory>
#include "LRUCache.h"
#include <exception>

namespace Azazel
{
    template <typename K, typename T>
    class ResourceManager
    {
    public:
        ResourceManager()
        {
        }

        virtual ~ResourceManager()
        {
        }

        virtual T loadResource(const K& path, bool needCache = true) = 0;
    protected:
        void cacheResource(const K& key, const T& resource)
        {
            lruCache.put(key, resource);
        }

        bool containsResource(const K& path)
        {
            return lruCache.contains(path);
        }

        T getResource(const K& path)
        {
            if (containsResource(path))
            {
                return lruCache.get(path)->second;
            }
            throw std::invalid_argument("No such resource for key: " + path);
        }

    private:
        LRUCache<K, T> lruCache;
    };
}