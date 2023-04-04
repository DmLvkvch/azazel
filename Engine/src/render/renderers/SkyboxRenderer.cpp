#include "SkyboxRenderer.h"

#include "resources/ResourceManager.h"
#include "render/MeshHelper.h"

namespace Azazel
{
    SkyboxRenderer::SkyboxRenderer()
    {
        
        mesh = MeshHelper::genSkybox();
        
        std::array<TextureData, 6> skyboxTextures;
        skyboxTextures[0] = ResourceManagers::textureDataResourceManager->loadResource("textures/skybox/right.jpg",  false, false);
        skyboxTextures[1] = ResourceManagers::textureDataResourceManager->loadResource("textures/skybox/left.jpg",   false, false);
        skyboxTextures[2] = ResourceManagers::textureDataResourceManager->loadResource("textures/skybox/top.jpg",    false, false);
        skyboxTextures[3] = ResourceManagers::textureDataResourceManager->loadResource("textures/skybox/bottom.jpg", false, false);
        skyboxTextures[4] = ResourceManagers::textureDataResourceManager->loadResource("textures/skybox/front.jpg",  false, false);
        skyboxTextures[5] = ResourceManagers::textureDataResourceManager->loadResource("textures/skybox/back.jpg",   false, false);
        cubeMap.reset(CubeMap::create(skyboxTextures));
        for (auto& textureData : skyboxTextures)
        {
            delete[] textureData.data;
        }
        shader.reset(Shader::create(FileUtils::readFile("shaders/skybox.vert.glsl"), FileUtils::readFile("shaders/skybox.frag.glsl")));
        
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