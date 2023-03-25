#pragma once

#include "AbstractResourceManager.h"
#include "render/Shader.h"
#include "api/file/FileUtils.h"
#include <utility>

namespace Azazel
{
    class ShaderResourceManager : public ResourceManager<std::string, std::shared_ptr<Shader>>
    {
    public:

        std::shared_ptr<Shader> loadResource(const std::string& path, bool needCache = true)
        {

            if (containsResource(path) && needCache)
            {
                return getResource(path);
            }
            const std::string fullCode = FileUtils::readFile(path);
            // TODO parse code
            std::shared_ptr<Shader> shader;
            return shader;
        }

        std::shared_ptr<Shader> loadResource(const std::string& vertexPath, const std::string& fragmentPath, bool needCache = true)
        {
            const std::string key = vertexPath + fragmentPath;

            if (containsResource(key) && needCache)
            {
                return getResource(key);
            }

            const std::string vertex = FileUtils::readFile(vertexPath);
            const std::string fragment = FileUtils::readFile(fragmentPath);

            std::shared_ptr<Shader> shader (Shader::create(vertex, fragment));
            if (needCache)
            {
                cacheResource(key, shader);
            }

            return shader;
        }
    };
}