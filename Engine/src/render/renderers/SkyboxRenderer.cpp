#include "SkyboxRenderer.h"

#include "resources/ResourceManager.h"

namespace Azazel
{
    SkyboxRenderer::SkyboxRenderer()
    {
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
            size_t sz = vertices.size() / 3;
            indices.resize(sz);
            
            for (unsigned int i = 0; i < sz; i++)
            {
                indices[i] = i;
            }

            std::array<TextureData, 6> skyboxTextures;

            skyboxTextures[0] = ResourceManagers::textureDataManager->loadResource("textures/skybox/right.jpg", false, false);
            skyboxTextures[1] = ResourceManagers::textureDataManager->loadResource("textures/skybox/left.jpg", false, false);
            skyboxTextures[2] = ResourceManagers::textureDataManager->loadResource("textures/skybox/top.jpg", false, false);
            skyboxTextures[3] = ResourceManagers::textureDataManager->loadResource("textures/skybox/bottom.jpg", false, false);
            skyboxTextures[4] = ResourceManagers::textureDataManager->loadResource("textures/skybox/front.jpg", false, false);
            skyboxTextures[5] = ResourceManagers::textureDataManager->loadResource("textures/skybox/back.jpg", false, false);

            mesh = Mesh<Vertex_P3>(vertices, indices);
            cubeMap.reset(CubeMap::create(skyboxTextures));

            for (auto& textureData : skyboxTextures)
            {
                delete[] textureData.data;
            }
            shader.reset(Shader::create(FileUtils::readFile("shaders/skybox.vert.glsl"), FileUtils::readFile("shaders/skybox.frag.glsl")));
        }
    }

    SkyboxRenderer::~SkyboxRenderer()
    {
        
    }

    void SkyboxRenderer::draw()
    {
        shader->bind();
        cubeMap->bind();
        Render::getRender()->drawMesh<Vertex_P3>(mesh, *shader);
    }
}