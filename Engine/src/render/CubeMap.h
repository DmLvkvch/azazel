#pragma once
#include <array>
#include "TextureData.h"

namespace Azazel
{
    class CubeMap
    {
    public:
        CubeMap();
        virtual ~CubeMap();

        virtual void bind() = 0;
        virtual void unbind() = 0;

        static CubeMap* create(std::array<TextureData, 6> textures);
    };
}