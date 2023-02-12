#include "ModelLoadLayer.h"

#include "FileUtils.h"
#include "TextureUtils.h"
#include "logging/Log.h"
#include "render/renderers/SkyboxRenderer.h"

namespace Azazel
{
    ModelLoadLayer::ModelLoadLayer() : Layer("Model Load Example")
    {
        model = Model("objects/duck/Duck.gltf");
        light.reset(Shader::create(FileUtils::readFile("shaders/light/phong.light.vert.glsl"), FileUtils::readFile("shaders/light/phong.light.frag.glsl")));
        
        texture.reset(Texture::create(TextureUtils::loadTexture("objects/duck/DuckCM.png")));
        model.transform.scale = glm::vec3 { 0.003f, 0.003f, 0.003f };
        camera = Camera();
    }

    void ModelLoadLayer::onUpdate(float delta)
    {
        texture->bind();
        //model.transform.rotation.y = (float) glfwGetTime() * 30.0f;

        glm::mat4 modelMatrix = model.transform.getTransformMatrix();

        glm::vec3 color (0.2f);
        float lightX = 2.0f * sin(glfwGetTime());
        float lightY = -0.3f;
        float lightZ = 1.5f * cos(glfwGetTime());
        glm::vec3 lightPos = glm::vec3(lightX, lightY, lightZ);

        glm::mat4 viewMatrix = glm::lookAt(lightPos, glm::vec3{0.0f, 0.0f, 0.0f}, glm::vec3{0.0f, 1.0f, 0.0f});
        glm::mat4 projectionMatrix = glm::perspective(glm::radians(45.0f), 1.5f, 0.1f, 100.0f);

        light->bind();
        light->setInt("u_texture_0", 0);
        light->setMatrix4f("u_mvp", projectionMatrix * viewMatrix * modelMatrix);
        light->setMatrix4f("u_model", modelMatrix);
        light->setMatrix4f("u_normalMatrix", glm::transpose(glm::inverse(modelMatrix)));

        light->setVec3f("u_light.ambient", color);
        light->setVec3f("u_light.diffuse", color);
        light->setVec3f("u_light.specular", color);
        light->setVec3f("u_light.position", {0.0f, 0.0f, -0.5f} );

        light->setVec3f("u_viewPos", {0.0f, 0.0f, -0.5f} );

        light->setVec3f("u_material.ambient", { 1.0f, 0.5f, 0.31f });
        light->setVec3f("u_material.diffuse", { 1.0f, 0.5f, 0.31f });
        light->setVec3f("u_material.specular", { 0.5f, 0.5f, 0.5f });
        light->setFloat("u_material.shininess", 128.0f);
    }

    void ModelLoadLayer::onRender(float delta)
    {
        sbr.draw();
        Render::getRender()->setDepthTest(true);
        Render::getRender()->setCullFace(true);
        model.draw(*light);
        Render::getRender()->setCullFace(false);
        Render::getRender()->setDepthTest(false);
    }
}