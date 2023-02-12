#pragma once

#include "render/Mesh.h"
#include "render/Vertex.h"
#include "render/CubeMap.h"
#include <memory>
#include "FileUtils.h"
#include "render/Render.h"

namespace Azazel
{
    class SkyboxRenderer
    {
    public:
        SkyboxRenderer()
        {
            std::vector<float> vertices
            {
                -1.0f,  1.0f, -1.0f,
                -1.0f, -1.0f, -1.0f,
                 1.0f, -1.0f, -1.0f,
                 1.0f, -1.0f, -1.0f,
                 1.0f,  1.0f, -1.0f,
                -1.0f,  1.0f, -1.0f,

                -1.0f, -1.0f,  1.0f,
                -1.0f, -1.0f, -1.0f,
                -1.0f,  1.0f, -1.0f,
                -1.0f,  1.0f, -1.0f,
                -1.0f,  1.0f,  1.0f,
                -1.0f, -1.0f,  1.0f,

                 1.0f, -1.0f, -1.0f,
                 1.0f, -1.0f,  1.0f,
                 1.0f,  1.0f,  1.0f,
                 1.0f,  1.0f,  1.0f,
                 1.0f,  1.0f, -1.0f,
                 1.0f, -1.0f, -1.0f,

                -1.0f, -1.0f,  1.0f,
                -1.0f,  1.0f,  1.0f,
                 1.0f,  1.0f,  1.0f,
                 1.0f,  1.0f,  1.0f,
                 1.0f, -1.0f,  1.0f,
                -1.0f, -1.0f,  1.0f,

                -1.0f,  1.0f, -1.0f,
                 1.0f,  1.0f, -1.0f,
                 1.0f,  1.0f,  1.0f,
                 1.0f,  1.0f,  1.0f,
                -1.0f,  1.0f,  1.0f,
                -1.0f,  1.0f, -1.0f,

                -1.0f, -1.0f, -1.0f,
                -1.0f, -1.0f,  1.0f,
                 1.0f, -1.0f, -1.0f,
                 1.0f, -1.0f, -1.0f,
                -1.0f, -1.0f,  1.0f,
                 1.0f, -1.0f,  1.0f  
            };
            std::vector<unsigned int> indices;
            for (unsigned int i = 0; i < vertices.size() / 3; i++)
            {
                indices.push_back(i);
            }

            mesh = Mesh<Vertex_P3>(vertices, indices);
            cubeMap.reset(CubeMap::create());
            shader.reset(Shader::create(FileUtils::readFile("shaders/skybox.vert.glsl"), FileUtils::readFile("shaders/skybox.frag.glsl")));
        }
        
        ~SkyboxRenderer()
        {

        }

        void draw()
        {
            shader->bind();
            shader->setMatrix4f("view", glm::mat4(1.0f));
            shader->setMatrix4f("projection", glm::mat4(1.0f));
            cubeMap->bind();
            Render::getRender()->drawMesh<Vertex_P3>(mesh, *shader);
        }

        std::unique_ptr<Shader> shader;
        std::unique_ptr<CubeMap> cubeMap;
        Mesh<Vertex_P3> mesh;
    };
}