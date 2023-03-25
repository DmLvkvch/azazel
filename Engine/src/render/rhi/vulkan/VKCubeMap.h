#pragma once

#include "render/CubeMap.h"

namespace Azazel
{
    class VKCubeMap : public CubeMap
    {
    public:
        VKCubeMap();
        ~VKCubeMap();
        void bind() const override;
        void unbind() const override;
    private:
        unsigned int textureID;
    };
}