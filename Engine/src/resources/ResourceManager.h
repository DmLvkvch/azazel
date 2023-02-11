#pragma once

#include <unordered_map>
#include <string>
#include "renderer/Shader.h"
#include "renderer/Texture.h"
#include <memory>

namespace Azazel
{
    template <typename T>
    class ResourceManager
    {
    public:
        virtual T loadResource(const std::string& path) = 0;
    private:
        std::unordered_map<std::string, T> resources;   
    };

    class TextureResourceManager : public ResourceManager<std::shared_ptr<Texture>>
    {
    public:
        std::shared_ptr<Texture> loadResource(const std::string& path)
        {
            return std::shared_ptr<Texture>();
        }
    private:
        static TextureResourceManager* textureManager;
    };

    class TextureDataResourceManager : public ResourceManager<std::shared_ptr<TextureData>>
    {
    public:
        std::shared_ptr<TextureData> loadResource(const std::string& path)
        {
            return std::shared_ptr<TextureData>();
        }
    private:
        static TextureDataResourceManager* textureDataManager;
    };

    class ShaderResourceManager : public ResourceManager<std::shared_ptr<Shader>>
    {
    public:
        std::shared_ptr<Shader> loadResource(const std::string& path)
        {
            return std::shared_ptr<Shader>();
        }
    private:
        static ShaderResourceManager* shaderManager;
    };
}