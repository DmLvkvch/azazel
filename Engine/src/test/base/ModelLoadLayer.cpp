#include "ModelLoadLayer.h"

namespace Azazel
{
    ModelLoadLayer::ModelLoadLayer() : Layer("Model Load Example")
    {
        model = Model::cube();
        shader.reset(Shader::create(FileUtils::readFile("shaders/solid.vert.glsl"), FileUtils::readFile("shaders/solid.frag.glsl")));
        light.reset(Shader::create(FileUtils::readFile("shaders/light/phong.light.vert.glsl"), FileUtils::readFile("shaders/light/phong.light.frag.glsl")));
        
        texture.reset(Texture::create(TextureUtils::loadTexture("objects/duck/DuckCM.png")));
        //model.transform.scale = glm::vec3{ 0.001f, 0.001f, 0.001f };
    }

    void ModelLoadLayer::onUpdate(float delta)
    {
        texture->bind();
        model.transform.rotation.x = model.transform.rotation.y = (float)glfwGetTime() * 30.0f;
        glm::mat4 t = glm::translate(glm::mat4(1.0f), glm::vec3{ -0.3f, 0.0f, 0.5f }) * model.transform.getTransformMatrix();
        
        light->bind();
        light->setInt("u_texture_0", 0);
        light->setMatrix4f("u_mvp", t);
        light->setMatrix4f("u_model", t);
        light->setMatrix4f("u_normalMatrix", glm::transpose(glm::inverse(t)));

        glm::vec3 lightColor;
        lightColor.x = static_cast<float>(sin(glfwGetTime() * 2.0));
        lightColor.y = static_cast<float>(sin(glfwGetTime() * 0.7));
        lightColor.z = static_cast<float>(sin(glfwGetTime() * 1.3));
        glm::vec3 diffuseColor = lightColor   * glm::vec3(0.5f);
        glm::vec3 ambientColor = glm::vec3(0.2f);
        light->setVec3f("u_light.ambient", ambientColor);
        light->setVec3f("u_light.diffuse", ambientColor);
        light->setVec3f("u_light.specular", ambientColor);
        light->setVec3f("u_light.position", {-0.3f, 0.0f, -0.7f} );

        light->setVec3f("u_material.ambient", { 1.0f, 0.5f, 0.31f });
        light->setVec3f("u_material.diffuse", { 1.0f, 0.5f, 0.31f });
        light->setVec3f("u_material.specular", { 0.5f, 0.5f, 0.5f });
        light->setFloat("u_material.shininess", 16.0f);

        light->setVec3f("u_viewPos", {-0.3f, 0.0f, 0.5f} );
    }

    void ModelLoadLayer::onRender(float delta)
    {
        Render::getRender()->setDepthTest(true);
        model.draw(*light);
        Render::getRender()->setDepthTest(false);
    }
}