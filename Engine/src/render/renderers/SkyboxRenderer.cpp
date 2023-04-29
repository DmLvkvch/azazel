#include "SkyboxRenderer.h"

#include "resources/ResourceManager.h"
#include "render/MeshHelper.h"

namespace Azazel
{
    SkyboxRenderer::SkyboxRenderer()
    {
        
        mesh = MeshHelper::genSkybox();
        
        std::array<TextureData, 6> skyboxTextures;
        skyboxTextures[0] = ResourceManagers::textureDataResourceManager->loadResource("textures/skybox/space/PositiveX.png", false, false);
        skyboxTextures[1] = ResourceManagers::textureDataResourceManager->loadResource("textures/skybox/space/NegativeX.png", false, false);
        skyboxTextures[2] = ResourceManagers::textureDataResourceManager->loadResource("textures/skybox/space/PositiveY.png", false, false);
        skyboxTextures[3] = ResourceManagers::textureDataResourceManager->loadResource("textures/skybox/space/NegativeY.png", false, false);
        skyboxTextures[4] = ResourceManagers::textureDataResourceManager->loadResource("textures/skybox/space/PositiveZ.png", false, false);
        skyboxTextures[5] = ResourceManagers::textureDataResourceManager->loadResource("textures/skybox/space/NegativeZ.png", false, false);
        cubeMap = CubeMap::create(skyboxTextures);
        for (auto& textureData : skyboxTextures)
        {
            TextureUtils::freeTextureData(textureData);
        }
        shader = Shader::create(FileUtils::readFile("shaders/skybox.vert.glsl"), FileUtils::readFile("shaders/skybox.frag.glsl"));
        
    }

    SkyboxRenderer::~SkyboxRenderer()
    {
        delete cubeMap;
        delete shader;
    }

    void SkyboxRenderer::draw()
    {
        Render::getRender()->setCullFace(false);
        shader->bind();
        auto camera = Render::getRender()->getCamera();
        shader->setMatrix4f("view", glm::mat4(glm::mat3(camera->getViewMatrix())));
        shader->setMatrix4f("projection", camera->getProjectionMatrix());
        cubeMap->bind();
        Render::getRender()->drawMesh(mesh, *shader);
        Render::getRender()->setCullFace(true);
    }
}