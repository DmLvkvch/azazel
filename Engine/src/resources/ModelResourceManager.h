#pragma once

#include "AbstractResourceManager.h"
#include "render/Model.h"

namespace Azazel
{
    class ModelResourceManager : public ResourceManager<std::string, Model*>
    {
    public:
        ModelResourceManager()
        {
            std::cout << "ModelResourceManager constructor" << std::endl;
        }

        virtual ~ModelResourceManager()
        {
            std::cout << "ModelResourceManager destructor" << std::endl;
        }

        Model* loadResource(const std::string& path, bool needCache = true)
        {
            return nullptr;
        }
    };
}
