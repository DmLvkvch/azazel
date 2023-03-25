#include "ModelLoadLayer.h"

#include "api/file/FileUtils.h"
#include "TextureUtils.h"
#include "logging/Log.h"
#include "render/renderers/SkyboxRenderer.h"
#include "Application.h"
#include <functional>
#include "resources/ResourceManager.h"

namespace Azazel
{
    ModelLoadLayer::ModelLoadLayer() : Layer("Model Load Example")
    {
        model = Model("objects/duck/Duck.gltf");
        light.reset(Shader::create(FileUtils::readFile("shaders/light/phong.light.vert.glsl"), FileUtils::readFile("shaders/light/phong.light.frag.glsl")));
        
        auto textureData = TextureUtils::loadTexture("objects/duck/DuckCM.png");

        texture.reset(Texture::create(textureData));

        delete[] textureData.data;

        TextureData square(500, 500, 0xffffffff);

        textureTest.reset(Texture::create(square));

        delete[] square.data;

        model.transform.scale = glm::vec3 { 0.0003f, 0.0003f, 0.0003f };
        camera = Camera();
        camera.subscribe();
    }

    ModelLoadLayer::~ModelLoadLayer()
    {
    }

    void ModelLoadLayer::onUpdate(float delta)
    {
        texture->bind();
        model.transform.scale = glm::vec3 { 0.0003f, 0.0003f, 0.0003f };
        model.transform.rotation.y = 0.0f;
        glm::mat4 modelMatrix = model.transform.getTransformMatrix();

        glm::vec3 color (0.2f);
        float lightX = 2.0f * (float) sin(glfwGetTime());
        float lightY = -0.3f;
        float lightZ = 1.5f * (float) cos(glfwGetTime());
        glm::vec3 lightPos = glm::vec3(lightX, lightY, lightZ);

        glm::mat4 viewMatrix = glm::lookAt(glm::vec3{1.0f, 1.0f, 0.0}, glm::vec3{0.0f, 0.0f, 0.0f}, glm::vec3{0.0f, 1.0f, 0.0f});
        glm::mat4 projectionMatrix = glm::perspective(glm::radians(45.0f), 1.5f, 0.1f, 100.0f);

        light->bind();
        light->setInt("u_texture_0", 0);
        camera.onInputUpdate(delta);
        light->setMatrix4f("u_mvp", camera.getProjectionMatrix() * camera.getViewMatrix() * modelMatrix);
        light->setMatrix4f("u_model", modelMatrix);
        light->setMatrix4f("u_normalMatrix", glm::transpose(glm::inverse(modelMatrix)));

        light->setVec3f("u_light.ambient", color);
        light->setVec3f("u_light.diffuse", color);
        light->setVec3f("u_light.specular", color);
        light->setVec3f("u_light.position", lightPos );

        light->setVec3f("u_viewPos", {1.0f, 1.0f, 0.0} );

        light->setVec3f("u_material.ambient", { 1.0f, 0.5f, 0.31f });
        light->setVec3f("u_material.diffuse", { 1.0f, 0.5f, 0.31f });
        light->setVec3f("u_material.specular", { 0.5f, 0.5f, 0.5f });
        light->setFloat("u_material.shininess", 128.0f);
        sbr.shader->bind();
        sbr.shader->setMatrix4f("view", glm::mat4(glm::mat3(camera.getViewMatrix())));
        sbr.shader->setMatrix4f("projection", camera.getProjectionMatrix());

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
        Render::getRender()->setDepthTest(true);
        sbr.draw();
        model.draw(*light);
        Render::getRender()->setDepthTest(false);
    }
}