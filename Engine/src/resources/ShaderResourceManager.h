#pragma once

#include "ResourceManager.h"
#include "render/Shader.h"

namespace Azazel
{
    class ShaderResourceManager : public ResourceManager<std::shared_ptr<Shader>>
    {
    public:
        std::shared_ptr<Shader> loadResource(const std::string& path, bool needCache = true)
        {
            return std::shared_ptr<Shader>();
        }
    private:
        static ShaderResourceManager* shaderManager;
    };
}