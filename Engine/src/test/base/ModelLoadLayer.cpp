#include "ModelLoadLayer.h"

#include "api/file/FileUtils.h"
#include "TextureUtils.h"
#include "logging/Log.h"
#include "render/renderers/SkyboxRenderer.h"
#include "render/renderers/TextRenderer.h"

#include "Application.h"
#include <functional>
#include "resources/ResourceManager.h"

namespace Azazel
{
    ModelLoadLayer::ModelLoadLayer() : Layer("Model Load Example")
    {
        model = Model("objects/duck/Duck.gltf");
        model.transform.scale = glm::vec3 { 0.003f, 0.003f, 0.003f };

       // model = Model::cube();
       // model.transform.scale = glm::vec3 { 0.3f, 0.3f, 0.3f };
       // model.transform.position.y += 0.05;

        floor = Model::floor();

        light.reset(Shader::create(FileUtils::readFile("shaders/light/phong.light.vert.glsl"), FileUtils::readFile("shaders/light/phong.light.frag.glsl")));

        auto textureData = TextureUtils::loadTexture("textures/container2.png");

        texture.reset(Texture::create(textureData));

        delete[] textureData.data;

        camera.subscribe();
        texture1.reset(Texture::create(TextureData(1024, 1024, 4, nullptr)));
        depthTexture.reset(Texture::createDepthTexture(1024, 1024));

        frameBuffer.reset(FrameBuffer::create(texture1.get(), depthTexture.get()));

        quad = MeshHelper::genQuadMesh();
        shadow.reset(Shader::create(FileUtils::readFile("shaders/shadow.vert.glsl"), FileUtils::readFile("shaders/shadow.frag.glsl")));
        shadowMap.reset(Shader::create(FileUtils::readFile("shaders/depth_map.vert.glsl"), FileUtils::readFile("shaders/depth_map.frag.glsl")));
        quadShader.reset(Shader::create(FileUtils::readFile("shaders/default.vert.glsl"), FileUtils::readFile("shaders/default.frag.glsl")));
        quadShader->bind();
        quadShader->setMatrix4f("u_mvp", glm::mat4(1.0f));
    }

    ModelLoadLayer::~ModelLoadLayer()
    {
        camera.unsubscribe();
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
        camera.onInputUpdate(delta);
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
        sbr.shader->bind();
        sbr.shader->setMatrix4f("view", glm::mat4(glm::mat3(camera.getViewMatrix())));
        sbr.shader->setMatrix4f("projection", camera.getProjectionMatrix());
        sbr.shader->unbind();

    }

    void ModelLoadLayer::onRender(float delta)
    {
        //glEnable(GL_DEPTH_TEST);
        //glEnable(GL_STENCIL_TEST);
//
        //glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);  
        //
        //glClear( GL_STENCIL_BUFFER_BIT); 
//
        //glStencilFunc(GL_ALWAYS, 1, 0x00);
        //glStencilMask(0xFF);        
//
        //texture->bind(0);
        //light->bind();
        //light->setInt("u_texture_0", 0);
        //model.draw(*light);
//
        //glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
        //glStencilMask(0x00);
//
        //model.transform.scale = glm::vec3 { 0.0004f, 0.0004f, 0.0004f };
        //model.transform.rotation.y = 0.0f
        //
        //textureTest->bind(0);
        //light->bind();
        //light->setMatrix4f("u_mvp", camera.getProjectionMatrix() * camera.getViewMatrix() * model.transform.getTransformMatrix());
        //light->setInt("u_texture_0", 0);
        //model.draw(*light);
        //glStencilMask(0xFF);
        //glStencilFunc(GL_ALWAYS, 1, 0xFF);
        auto renderer = Render::getRender();
        renderer->setDepthTest(true);

        glm::mat4 lightProjection = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, 1.0f, 7.5f);

        glm::vec3 lightPos(-2.0f, 4.0f, -1.0f);
        lightPos.x = sin(glfwGetTime()) * 3.0f;
        lightPos.z = cos(glfwGetTime()) * 2.0f;
        lightPos.y = 5.0 + cos(glfwGetTime()) * 1.0f;

        glm::mat4 lightView = glm::lookAt(lightPos, glm::vec3(0.0f), glm::vec3(0.0, 1.0, 0.0));
        glm::mat4 lightSpaceMatrix = lightProjection * lightView;
        
        auto floorModel = floor.transform.getTransformMatrix();
        auto modelModel = model.transform.getTransformMatrix();


        shadowMap->bind();
        shadowMap->setMatrix4f("lightSpaceMatrix", lightSpaceMatrix);
        renderer->setDepthTest(true);
        renderer->setViewport(0, 0, 1024, 1024);
        
        frameBuffer->bind();

        renderer->clear(false, true, true);
        shadowMap->setMatrix4f("model", floorModel);
        floor.draw(*shadowMap);

        shadowMap->setMatrix4f("model", modelModel);
        model.draw(*shadowMap);

        frameBuffer->unbind();

        renderer->setViewport(0, 0, 1280, 720);
        shadow->bind();

        shadow->setVec3f("viewPos", camera.cameraLocation.position);
        shadow->setVec3f("lightPos", lightPos);
        shadow->setMatrix4f("lightSpaceMatrix", lightSpaceMatrix);
        shadow->setTexture("diffuseTexture", *texture, 0);
        shadow->setTexture("shadowMap", *depthTexture, 1);

        shadow->setMatrix4f("model", floorModel);
        shadow->setMatrix4f(Shader::UNIFORM_MVP_MATRIX, camera.getProjectionMatrix() * camera.getViewMatrix() * floorModel);
        floor.draw(*shadow);

        shadow->setMatrix4f("model", modelModel);
        shadow->setMatrix4f(Shader::UNIFORM_MVP_MATRIX, camera.getProjectionMatrix() * camera.getViewMatrix() * modelModel);
        model.draw(*shadow);
        renderer->setDepthFunc(CompareFunction::LESS_EQUAL);
        //sbr.draw();
        renderer->setDepthFunc(CompareFunction::LESS);
        depthTexture->bind();
        renderer->drawMesh<Vertex_P3_T2>(quad, *quadShader);
    }
}