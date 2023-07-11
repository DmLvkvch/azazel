#include "ModelLoadLayer.h"

#include "api/file/FileUtils.h"
#include "TextureUtils.h"
#include "logging/Log.h"
#include <functional>
#include "resources/ResourceManager.h"
#include "render/ModelHelper.h"
#include <nlohmann/json.hpp>

namespace Azazel
{
    ModelLoadLayer::ModelLoadLayer() : Layer("Model Load Example")
    {
        model = ResourceManagers::getModelResourceManager().loadResource("objects/Sponza/cfg.json");

        cube = ResourceManagers::getModelResourceManager().loadResource("objects/earth/cfg.json");

        floor = ModelHelper::floor();

        sphere = ModelHelper::sphere(36, 36);
        sphere.transform.scale = { 0.5f, 0.5f, 0.5f };

        cerberus = ResourceManagers::getModelResourceManager().loadResource("objects/cerberus/cfg.json");

        depthTexture = Texture::createDepthTexture(1024, 1024);

        frameBuffer = FrameBuffer::create(nullptr, depthTexture);

        quad = MeshHelper::genQuadMesh();
        shadow = ResourceManagers::getShaderResourceManager().loadResource("shaders/shadow.vert.glsl", "shaders/shadow.frag.glsl", false);
        shadowMap = ResourceManagers::getShaderResourceManager().loadResource("shaders/depth_map.vert.glsl", "shaders/depth_map.frag.glsl", false);
    }

    ModelLoadLayer::~ModelLoadLayer()
    {
        delete shadow;
        delete shadowMap;
        delete frameBuffer;
        delete depthTexture;
    }

    void ModelLoadLayer::onUpdate(float delta)
    {
        cube.transform.rotation.y += delta / 10.0f;
    }

    void ModelLoadLayer::onRender(float delta)
    {
        auto renderer = Render::getRender();
        auto camera = renderer->getCamera();
        
        renderer->setDepthTest(true);
        glm::mat4 lightProjection = glm::ortho(-15.0f, 15.0f, -15.0f, 15.0f, -30.f, 30.f);

        glm::vec3 lightPos {0.0f, 5.0f, 0.0f};

        // lightPos.x = 0.0f + sin(glfwGetTime()) * 5.0f;
        // lightPos.z = cos(glfwGetTime()) * 10.0f;
        // lightPos.y = 8.0f + 4.0f * cos(glfwGetTime());

        sphere.transform.position = lightPos;

        glm::mat4 lightView = glm::lookAt(lightPos, glm::vec3(0.0f), glm::vec3(0.0, 1.0, 0.0));
        glm::mat4 lightSpaceMatrix = lightProjection * lightView;

        auto floorModel = floor.transform.getTransformMatrix();
        auto modelModel = model.transform.getTransformMatrix();

        shadowMap->bind();
        shadowMap->setMatrix4f("lightSpaceMatrix", lightSpaceMatrix);


        frameBuffer->bind();
        renderer->setViewport(Viewport {0, 0, 1024, 1024});
        renderer->setCullFace(true);
        renderer->setCullFaceMode(CullMode::FRONT);
        renderer->clear(true, true, true);

        floor.draw(*shadowMap);
        cerberus.draw(*shadowMap);
        model.draw(*shadowMap);

        cube.draw(*shadowMap);

        sphere.draw(*shadowMap);

        frameBuffer->unbind();

        shadowMap->unbind();

        renderer->popViewport();
        renderer->setCullFaceMode(CullMode::BACK);

        shadow->bind();
        shadow->setVec3f("viewPos", camera->cameraLocation.position);
        shadow->setVec3f("lightPos", lightPos);
        shadow->setMatrix4f("lightSpaceMatrix", lightSpaceMatrix);
        shadow->setTexture("shadowMap", *depthTexture, 1);

        shadow->setMatrix4f(Shader::UNIFORM_MVP_MATRIX, camera->getViewProjectionMatrix() * floorModel);
        floor.draw(*shadow);

        shadow->setMatrix4f(Shader::UNIFORM_MVP_MATRIX, camera->getViewProjectionMatrix() * modelModel);
        model.draw(*shadow);

        shadow->setMatrix4f(Shader::UNIFORM_MVP_MATRIX, camera->getViewProjectionMatrix() * cube.transform.getTransformMatrix());
        cube.draw(*shadow);

        shadow->setMatrix4f(Shader::UNIFORM_MVP_MATRIX, camera->getViewProjectionMatrix() * sphere.transform.getTransformMatrix());
        sphere.draw(*shadow);

        shadow->setMatrix4f(Shader::UNIFORM_MVP_MATRIX, camera->getViewProjectionMatrix() * cerberus.transform.getTransformMatrix());
        cerberus.draw(*shadow);
        shadow->unbind();

        renderer->setDepthFunc(CompareFunction::LESS_EQUAL);
        sbr.draw();
        renderer->setDepthFunc(CompareFunction::LESS);
    }
}