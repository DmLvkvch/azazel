#pragma once

#include "AbstractResourceManager.h"
#include "render/Model.h"
#include "TextureUtils.h"

namespace Azazel
{
    class ModelResourceManager : public ResourceManager<std::string, std::shared_ptr<Model>>
    {
    public:
        std::shared_ptr<Model> loadResource(const std::string& path, bool needCache = true)
        {
            return std::shared_ptr<Model> ();
        }
    };
}
