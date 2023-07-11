#pragma once

#include "AbstractResourceManager.h"
#include "render/Model.h"
#include <fstream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

namespace Azazel
{
    class ModelResourceManager : public ResourceManager<std::string, Model>
    {
    public:
        ModelResourceManager()
        {
        }

        virtual ~ModelResourceManager()
        {
        }


        Model loadResource(const std::string& path, bool needCache = true)
        {
            std::ifstream f(path);
            json data = json::parse(f);
            
            glm::vec3 scale    = {(float) data["transform"]["scale"]["x"], (float) data["transform"]["scale"]["y"], (float) data["transform"]["scale"]["z"]};            
            glm::vec3 rotation = {(float) data["transform"]["rotation"]["x"], (float) data["transform"]["rotation"]["y"], (float) data["transform"]["rotation"]["z"]};
            glm::vec3 position = {(float) data["transform"]["position"]["x"], (float) data["transform"]["position"]["y"], (float) data["transform"]["position"]["z"]};
            
            size_t pos = path.find_last_of("\\/");
            std::string dir = (std::string::npos == pos) ? "" : path.substr(0, pos);

            std::string modelPath = dir + "/" + std::string(data["model"]);

            Model model = Model::createModel(modelPath);
            model.transform.position = position;
            model.transform.scale = scale;
            model.transform.rotation = rotation;

            return model;
        }
    };
}
