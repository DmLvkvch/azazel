#pragma once

#include "render/Mesh.h"
#include "render/Vertex.h"
#include "render/Texture.h"
#include "render/Render.h"

namespace Azazel
{
    class SkyboxRenderer
    {
    public:
        SkyboxRenderer();
        ~SkyboxRenderer();
        void draw();

    private:
        Shader* shader;
        CubeMap* cubeMap;
        Mesh mesh;
    };
}