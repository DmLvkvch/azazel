#pragma once

#include <Layer.h>
#include <renderer/Model.h>
#include <renderer/Mesh.h>
#include <renderer/Vertex.h>
#include <FileUtils.h>
#include <TextureUtils.h>

namespace Azazel
{
    class ModelLoadLayer : public Layer
    {
    public:
        ModelLoadLayer() : Layer("Model Load Example")
        {
            model = Model("objects/backpack/cottage_fbx.fbx");
            shader.reset(Shader::create(FileUtils::readFile("shaders/solid.vert.glsl"), FileUtils::readFile("shaders/solid.frag.glsl")));
            texture.reset(Texture::create(TextureUtils::loadTexture("objects/backpack/cottage_10.jpg")));
        }

        void onUpdate(float delta) override
        {
            Render::getRender()->setDepthTest(true);
            shader->bind();
            texture->bind();
            shader->setInt("u_texture_0", 0);
            shader->setMatrix4f("u_mvp", glm::translate(glm::mat4(1.0f), glm::vec3{-0.3f, 0.0f, 0.5f}) * glm::rotate(glm::mat4(1.0f), glm::radians((float) glfwGetTime()* 10.0f), {0.0f, 1.0f, 1.0f}) * glm::scale(glm::mat4(1.0f), glm::vec3(0.1f, 0.1f, 0.1f)));
            model.draw(*shader);
            Render::getRender()->setDepthTest(false);
        }

        ~ModelLoadLayer() {}
    private:
        std::unique_ptr<Shader> shader;
        std::unique_ptr<Texture> texture;
        Model model;
    };
}