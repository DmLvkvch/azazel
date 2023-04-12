#pragma once

#include "render/Texture.h"

namespace Azazel
{
    class GLESCubeMap : public CubeMap
    {
    public:
        GLESCubeMap(std::array<TextureData, 6> textures);
        ~GLESCubeMap();
        void bind(int slot = 0) const override;
        void unbind() const override;
    private:
        unsigned int textureID;
    };
}