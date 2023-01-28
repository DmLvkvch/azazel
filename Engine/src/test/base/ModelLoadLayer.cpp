#include "ModelLoadLayer.h"

namespace Azazel
{
    ModelLoadLayer::ModelLoadLayer() : Layer("Model Load Example")
    {
        model = Model::cube();
        shader.reset(Shader::create(FileUtils::readFile("shaders/solid.vert.glsl"), FileUtils::readFile("shaders/solid.frag.glsl")));
        light.reset(Shader::create(FileUtils::readFile("shaders/light/phong.light.vert.glsl"), FileUtils::readFile("shaders/light/phong.light.frag.glsl")));
        
        texture.reset(Texture::create(TextureUtils::loadTexture("objects/duck/DuckCM.png")));
        model.transform.scale = glm::vec3 { 0.3f, 0.3f, 0.3f };
    }

    void ModelLoadLayer::onUpdate(float delta)
    {
        texture->bind();
        model.transform.rotation.x = (float)glfwGetTime() * 30.0f;
        glm::mat4 modelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3{ -0.0f, 0.0f, -0.1f }) * model.transform.getTransformMatrix();
        
        glm::mat4 viewMatrix(1.0f);
        glm::mat4 projectionMatrix(1.0f);

        light->bind();
        light->setInt("u_texture_0", 0);
        light->setMatrix4f("u_mvp", projectionMatrix * viewMatrix * modelMatrix);
        light->setMatrix4f("u_model", modelMatrix);
        light->setMatrix4f("u_normalMatrix", glm::transpose(glm::inverse(modelMatrix)));

        glm::vec3 color(0.2f);
        light->setVec3f("u_light.ambient", color);
        light->setVec3f("u_light.diffuse", color);
        light->setVec3f("u_light.specular", color);
        light->setVec3f("u_light.position", {0.0f, 0.0f, 1.0f} );

        light->setVec3f("u_viewPos", {0.0f, 0.0f, 0.0f} );

        light->setVec3f("u_material.ambient", { 1.0f, 0.5f, 0.31f });
        light->setVec3f("u_material.diffuse", { 1.0f, 0.5f, 0.31f });
        light->setVec3f("u_material.specular", { 0.5f, 0.5f, 0.5f });
        light->setFloat("u_material.shininess", 128.0f);
    }

    void ModelLoadLayer::onRender(float delta)
    {
        Render::getRender()->setDepthTest(true);
        model.draw(*light);
        Render::getRender()->setDepthTest(false);
    }
}