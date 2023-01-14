#include "BaseLayer.h"

#include <TextureUtils.h>
#include <FileUtils.h>
#include <events/KeyEvent.h>
#include <events/MouseEvent.h>
#include <events/ApplicationEvent.h>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <renderer/Render.h>

namespace Azazel
{
    void BaseLayer::onAttach()
    {
        std::vector<float> vertices 
        {
            0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
            0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
            -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
            -0.5f,  0.5f, 0.0f, 0.0f, 1.0f
        };

        std::vector<unsigned int> indices {0, 1, 3, 1, 2, 3};
        std::shared_ptr<VertexBuffer> vertexBuffer (VertexBuffer::create((float*) vertices.data(), sizeof(float) * vertices.size()));
        indexBuffer.reset(IndexBuffer::create(indices.data(), 6));
        vertexArray.reset(VertexArray::create());
        BufferLayout bf = 
        {
            { ShaderDataType::Float3, "a_position" },
            { ShaderDataType::Float2, "a_texture_coord" }
        };
        vertexArray->addBuffer(vertexBuffer, bf);

        shader.reset(Shader::create(FileUtils::readFile("shaders/default.vert.glsl"), FileUtils::readFile("shaders/default.frag.glsl")));
        texture.reset(Texture::create(TextureUtils::loadTexture("images/awesomeface.png")));
        texture->setTextureFilter(Texture::TextureFilter::Linear);
        shader->bind();
        shader->setMatrix4f("u_mvp", glm::mat4(1.0f));
        camera = OrthographicCamera(0, 960, 0, 540);
        texture.reset(Texture::create(TextureData(500, 500, 0xff0000ff)));
        texture1.reset(Texture::create(TextureData(500, 500, 0x0000fff0)));

        transform.scale = { 100.0f, 100.0f, 0.0f };
        color = {0.0f, 0.0f, 0.0f, 1.0f};
    }

    void BaseLayer::onDetach()
    {

    }

    void BaseLayer::onUpdate(float delta)
    {
        shader->bind();
        shader->setMatrix4f("u_mvp", camera.getViewProjectionMatrix() * transform.getTransformMatrix());
        Render::getRender()->drawIndexed(*vertexArray, *indexBuffer, *shader, *texture);

        shader->bind();
        shader->setMatrix4f("u_mvp", camera.getViewProjectionMatrix() * glm::translate(glm::mat4(1.0f), glm::vec3(400.0f, 400.0f, 0.0f)) * glm::scale(glm::mat4(1.0f), glm::vec3(200.0f, 200.0f, 1.0f)));
        Render::getRender()->drawIndexed(*vertexArray, *indexBuffer, *shader, *texture1);
    }

    void BaseLayer::onImguiRender(float delta)
    {
        drawImgui();
    }

    void BaseLayer::drawImgui()
    {
        ImGui::Begin("Transform");
     
        ImGui::ColorEdit4("Texture Color", &color.x);
        ImGui::SliderFloat2("translation", &transform.position.x, 0, 600.0f);
        ImGui::SliderFloat("rotation", &transform.rotation.z, 0.0f, 360.0f);
        ImGui::SliderFloat2("scale", &transform.scale.x, 0.0f, 200.0f);

        std::vector<std::string> listbox_items { "images/awesomeface.png", "images/cat.png", "images/grass.png", "images/flower.jpg", "images/small_image.png", "images/blending_transparent_window.png"  };
        if (ImGui::ListBoxHeader("Textures", listbox_items.size()))
        {
            for (auto& item : listbox_items)
            {
                if (ImGui::Selectable(item.c_str()))
                {
                    texture.reset(Texture::create(TextureUtils::loadTexture(item)));
                }
            }
            ImGui::ListBoxFooter();
        }
        updateBlendEquation();
        ImGui::End();
    }

    void BaseLayer::updateBlendEquation()
    {
        std::vector<std::string> equations { "GL_FUNC_ADD", "GL_FUNC_SUBTRACT", "GL_FUNC_REVERSE_SUBTRACT", "GL_MIN", "GL_MAX"};
        if (ImGui::ListBoxHeader("Blend equation", equations.size()))
        {
            for (auto& item : equations)
            {
                if (ImGui::Selectable(item.c_str()))
                {
                    if (item == "GL_FUNC_ADD")
                    {
                        Render::getRender()->setBlendEquation(BlendEquation::Add);
                    }
                    else if (item == "GL_FUNC_SUBTRACT")
                    {
                        Render::getRender()->setBlendEquation(BlendEquation::Subtract);
                    }
                    else if (item == "GL_FUNC_REVERSE_SUBTRACT")
                    {
                        Render::getRender()->setBlendEquation(BlendEquation::ReverseSubtract);
                    }
                    else if (item == "GL_MIN")
                    {
                        Render::getRender()->setBlendEquation(BlendEquation::Min);
                    }
                    else if (item == "GL_MAX")
                    {
                        Render::getRender()->setBlendEquation(BlendEquation::Max);
                    }
                }
            }
            ImGui::ListBoxFooter();
        }
    }

    void BaseLayer::onEvent(Event& e)
    {
    }
}