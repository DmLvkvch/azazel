#pragma once
#include <vector>
#include <string>

namespace Azazel
{
    class VKTextureCubeMap
    {
    public:
        VKTextureCubeMap(std::vector<std::string> textures);
        ~VKTextureCubeMap();
        void bind(int slot = 0);
        void unbind();
    private:
        unsigned int rendererID;
    };
}