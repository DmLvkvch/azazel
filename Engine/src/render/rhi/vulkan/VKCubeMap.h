#pragma once

#include "render/CubeMap.h"

namespace Azazel
{
    class VKCubeMap : public CubeMap
    {
    public:
        VKCubeMap();
        ~VKCubeMap();
        void bind() override;
        void unbind() override;
    private:
        unsigned int textureID;
    };
}