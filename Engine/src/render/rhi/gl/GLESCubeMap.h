#pragma once

#include "render/CubeMap.h"

namespace Azazel
{
    class GLESCubeMap : public CubeMap
    {
    public:
        GLESCubeMap(std::array<TextureData, 6> textures);
        ~GLESCubeMap();
        void bind() const override;
        void unbind() const override;
    private:
        unsigned int textureID;
    };
}