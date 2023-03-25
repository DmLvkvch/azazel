#pragma once

#include "render/Mesh.h"
#include "render/Vertex.h"
#include "render/CubeMap.h"
#include <memory>
#include "api/file/FileUtils.h"
#include "render/Render.h"

namespace Azazel
{
    class SkyboxRenderer
    {
    public:
        SkyboxRenderer();
        ~SkyboxRenderer();
        void draw();
    public:
        std::unique_ptr<Shader> shader;
    private:
        std::unique_ptr<CubeMap> cubeMap;
        Mesh<Vertex_P3> mesh;
    };
}