#pragma once

#include "AbstractResourceManager.h"
#include "render/Model.h"
#include "TextureUtils.h"

namespace Azazel
{
    class ModelResourceManager : public ResourceManager<std::string, Model*>
    {
    public:
        Model* loadResource(const std::string& path, bool needCache = true)
        {
            return nullptr;
        }
    };
}
