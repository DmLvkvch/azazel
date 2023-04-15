#pragma once

#include <unordered_map>
#include <list>
#include <cstddef>
#include <stdexcept>

namespace Azazel
{
    template<typename key_t, typename value_t>
    class LRUCache
    {
    public:
        using key_value_pair_t = std::pair<key_t, value_t>;
        using list_iterator_t = typename std::list<key_value_pair_t>::iterator;

        LRUCache(int size = 50): 
        sz(size)
        {
        }

        void put(const key_t& key, const value_t& value)
        {
            auto it = cacheMap.find(key);
            cacheList.push_front(key_value_pair_t(key, value));
            if (it != cacheMap.end()) 
            {
                cacheList.erase(it->second);
                cacheMap.erase(it);
            }
            
            cacheMap[key] = cacheList.begin();
            
            if (cacheMap.size() > sz && sz >= 0)
            {
                auto last = --cacheList.end();
                cacheMap.erase(last->first);
                cacheList.pop_back();
            }
        }

        const list_iterator_t get(const key_t& key)
        {
            auto it = cacheMap.find(key);
            if (it == cacheMap.end()) 
            {
                //throw std::range_error("Key not found!");
                return end();
            } 
            cacheList.splice(cacheList.begin(), cacheList, it->second);
            return it->second;
        }

        list_iterator_t begin()
        {
            return cacheList.begin();
        }

        list_iterator_t end()
        {
            return cacheList.end();
        }

        bool contains(const key_t& key)
        {
            return cacheMap.find(key) != cacheMap.end();
        }

        int size() const
        {
            return cacheMap.size();
        }

    private:
        int sz;
        std::list<key_value_pair_t> cacheList;
        std::unordered_map<key_t, list_iterator_t> cacheMap;
    };
}