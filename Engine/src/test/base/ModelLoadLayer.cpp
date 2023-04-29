#include "ModelLoadLayer.h"

#include "api/file/FileUtils.h"
#include "TextureUtils.h"
#include "logging/Log.h"
#include <functional>
#include "resources/ResourceManager.h"
#include "render/ModelHelper.h"

namespace Azazel
{
    ModelLoadLayer::ModelLoadLayer() : Layer("Model Load Example")
    {
        model = Model::createModel("objects/Sponza/sponza.info", 0);
        model = Model::createModel("objects/Sponza/Sponza.gltf");
        model.transform.scale = { 0.003f, 0.003f, 0.003f };
        model.transform.position.y = 0.2f;

        cube = Model::createModel("objects/earth/Earth.glb");
        cube.transform.scale = { 0.007f, 0.007f, 0.007f };
        cube.transform.position.x = 10.5f;
        cube.transform.position.y = 8.0f;

        floor = ModelHelper::floor();
        floor.transform.scale = { 20.0f, 20.0f, 1.0f };
        floor.transform.rotation.x = -90.0f;
        floor.transform.position.x = -10.0f;
        floor.transform.position.z = 10.0f;

        sphere = ModelHelper::sphere(36, 36);
        sphere.transform.scale = { 0.5f, 0.5f, 0.5f };

        cerberus = Model::createModel("objects/cerberus/cerberus.fbx");
        cerberus.transform.scale = { 0.007f, 0.007f, 0.007f };
        cerberus.transform.position.y += 0.9f;
        cerberus.transform.rotation.x -= 90.0f;
        cerberus.transform.rotation.z -= 90.0f;

        depthTexture = Texture::createDepthTexture(1024, 1024);

        frameBuffer = FrameBuffer::create(nullptr, depthTexture);

        quad = MeshHelper::genQuadMesh();
        shadow = ResourceManagers::shaderResourceManager->loadResource("shaders/shadow.vert.glsl", "shaders/shadow.frag.glsl", false);
        shadowMap = ResourceManagers::shaderResourceManager->loadResource("shaders/depth_map.vert.glsl", "shaders/depth_map.frag.glsl", false);
        quadShader = ResourceManagers::shaderResourceManager->loadResource("shaders/shadow_map.debug.vert.glsl", "shaders/shadow_map.debug.frag.glsl", false);
        quadShader->bind();
        quadShader->setMatrix4f("u_mvp", glm::mat4(1.0f));
        quadShader->setFloat("near_plane", 1.0f);
        quadShader->setFloat("far_plane", 10.5f);
    }

    ModelLoadLayer::~ModelLoadLayer()
    {
        delete shadow;
        delete shadowMap;
        delete quadShader;
        delete frameBuffer;
        delete depthTexture;
    }

    void ModelLoadLayer::onUpdate(float delta)
    {
        //  model.transform.rotation.x = 180 / 3.14f * static_cast<float>(sin(glfwGetTime()));
        //  glm::mat4 modelMatrix = model.transform.getTransformMatrix();
  //
        //  glm::vec3 color (0.2f);
        //  float lightX = 2.0f * static_cast<float>(sin(glfwGetTime()));
        //  float lightY = -0.3f;
        //  float lightZ = 1.5f * static_cast<float>(cos(glfwGetTime()));
        //  glm::vec3 lightPos = glm::vec3(lightX, lightY, lightZ);
  //
        //  light->bind();
        //  light->setTexture(Shader::UNIFORM_TEXTURE0, *texture);
        //  light->setMatrix4f(Shader::UNIFORM_MVP_MATRIX, camera.getProjectionMatrix() * camera.getViewMatrix() * modelMatrix);
        //  light->setMatrix4f(Shader::UNIFORM_MODEL_MATRIX, modelMatrix);
        //  light->setMatrix4f(Shader::UNIFORM_NORMAL_MATRIX, glm::transpose(glm::inverse(modelMatrix)));
  //
        //  light->setVec3f("u_light.ambient", color);
        //  light->setVec3f("u_light.diffuse", color);
        //  light->setVec3f("u_light.specular", color);
        //  light->setVec3f("u_light.position", lightPos );
  //
        //  light->setVec3f("u_viewPos", {1.0f, 1.0f, 0.0} );
  //
        //  light->setVec3f("u_material.ambient", { 1.0f, 0.5f, 0.31f });
        //  light->setVec3f("u_material.diffuse", { 1.0f, 0.5f, 0.31f });
        //  light->setVec3f("u_material.specular", { 0.5f, 0.5f, 0.5f });
        //  light->setFloat("u_material.shininess", 128.0f);
        cube.transform.rotation.y += delta / 10.0f;
    }

    void ModelLoadLayer::onRender(float delta)
    {
        auto renderer = Render::getRender();
        auto camera = renderer->getCamera();
        
        renderer->setDepthTest(true);
        glm::mat4 lightProjection = glm::ortho(-15.0f, 15.0f, -15.0f, 15.0f, -30.f, 30.f);

        glm::vec3 lightPos;

        lightPos.x = 1.0f;
        lightPos.z = -0.3f;
        lightPos.y = -0.1f;

        sphere.transform.position = lightPos;

        glm::mat4 lightView = glm::lookAt(lightPos, glm::vec3(0.0f), glm::vec3(0.0, 1.0, 0.0));
        glm::mat4 lightSpaceMatrix = lightProjection * lightView;

        auto floorModel = floor.transform.getTransformMatrix();
        auto modelModel = model.transform.getTransformMatrix();

        shadowMap->bind();
        shadowMap->setMatrix4f("lightSpaceMatrix", lightSpaceMatrix);

        renderer->setViewport(0, 0, 1280, 1024);

        frameBuffer->bind();

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

      //  hdrRenderer.bind();
      
    //    renderer->clear(true, true, true);
        renderer->setViewport(0, 0, 1280, 720);
        renderer->setCullFaceMode(CullMode::BACK);

       // renderer->setViewport(0, 0, 1024, 1024);

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
     //   depthTexture->bind();
     //   renderer->drawMesh<Vertex_P3_T2>(quad, *quadShader);
        //renderer->setViewport(0, 0, 1280, 720);
        //hdrRenderer.unbind();
        //hdrRenderer.draw();
    }
}