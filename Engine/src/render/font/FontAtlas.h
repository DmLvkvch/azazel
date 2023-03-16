#pragma once

#include "render/Mesh.h"
#include "render/Vertex.h"
#include <string>

namespace Azazel
{
    class FontAtlas
    {
    public:
        FontAtlas(int size)
        : size(size)
        {
            atlas = new char[size * size];
        }

        Mesh<Vertex_P3_T2> renderText(std::string& text);

    private:
        int size;
        unsigned char* atlas;
    };
}