#pragma once
#include <vector>
#include <string>

namespace Azazel
{
    class GLESTextureCubeMap
    {
    public:
        GLESTextureCubeMap(std::vector<std::string> textures);
        ~GLESTextureCubeMap();
        void bind(int slot = 0);
        void unbind();
    private:
        unsigned int rendererID;
    };
}