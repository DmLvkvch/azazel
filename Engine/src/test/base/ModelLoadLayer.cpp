#include "ModelLoadLayer.h"

Azazel::ModelLoadLayer::ModelLoadLayer() : Layer("Model Load Example")
{
    model = Model("objects/duck/Duck.gltf");
    shader.reset(Shader::create(FileUtils::readFile("shaders/solid.vert.glsl"), FileUtils::readFile("shaders/solid.frag.glsl")));
    light.reset(Shader::create(FileUtils::readFile("shaders/light/phong.light.vert.glsl"), FileUtils::readFile("shaders/light/phong.light.frag.glsl")));
    
    texture.reset(Texture::create(TextureUtils::loadTexture("objects/duck/DuckCM.png")));
    model.transform.scale = glm::vec3{ 0.001f, 0.001f, 0.001f };
}

void Azazel::ModelLoadLayer::onUpdate(float delta)
{
    Render::getRender()->setDepthTest(true);
    texture->bind();
    model.transform.rotation.x = model.transform.rotation.y = (float)glfwGetTime() * 30.0f;
    glm::mat4 t = glm::translate(glm::mat4(1.0f), glm::vec3{ -0.3f, 0.0f, 0.5f }) * model.transform.getTransformMatrix();
    
    light->bind();
    light->setInt("u_texture_0", 0);
    light->setMatrix4f("u_mvp", t);
    light->setMatrix4f("u_model", t);
    light->setMatrix4f("u_normalMatrix", glm::transpose(glm::inverse(t)));

    light->setVec3f("u_material.color", glm::vec3(1.0f, 0.0f, 1.0f));
    light->setFloat("u_material.shininess", 32.0f);
    light->setVec3f("u_lightPos", glm::vec3 {-0.3f, 0.0f, -0.7f} );
    light->setVec3f("u_viewPos", glm::vec3 {-0.3f, 0.0f, 0.5f} );


    model.draw(*light);
    Render::getRender()->setDepthTest(false);
}
