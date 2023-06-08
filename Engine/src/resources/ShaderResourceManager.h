#pragma once

#include "AbstractResourceManager.h"
#include "render/Shader.h"
#include "api/file/FileUtils.h"
#include <utility>

namespace Azazel
{
    class ShaderResourceManager : public ResourceManager<std::string, Shader*>
    {
    public:
        ShaderResourceManager()
        {
            std::cout << "ShaderResourceManager constructor" << std::endl;
        }
        
        virtual ~ShaderResourceManager()
        {
            std::cout << "ShaderResourceManager destructor" << std::endl;
        }

        Shader* loadResource(const std::string& path, bool needCache = true)
        {

            if (needCache && containsResource(path))
            {
                return getResource(path);
            }
            const std::string fullCode = FileUtils::readFile(path);
            // TODO parse code
            return nullptr;
        }

        Shader* loadResource(const std::string& vertexPath, const std::string& fragmentPath, bool needCache = true)
        {
            const std::string key = vertexPath + fragmentPath;

            if (needCache && containsResource(key))
            {
                return getResource(key);
            }

            const std::string vertex = FileUtils::readFile(vertexPath);
            const std::string fragment = FileUtils::readFile(fragmentPath);

            Shader* shader (Shader::create(vertex, fragment));
            if (needCache)
            {
                cacheResource(key, shader);
            }

            return shader;
        }
    };
}