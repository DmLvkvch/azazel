#pragma once

#include "render/Texture.h"

namespace Azazel
{
    class VKCubeMap : public CubeMap
    {
    public:
        VKCubeMap();
        ~VKCubeMap();
        void bind(int slot) const override;
        void unbind() const override;
    private:
        unsigned int textureID;
    };
}