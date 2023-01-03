#include "BaseLayer.h"
#define _CRTDBG_MAP_ALLOC

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
    BaseLayer::~BaseLayer()
    {

    }

    void BaseLayer::onAttach()
    {
        std::vector<float> vertices = {
                            0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
                            0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
                            -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
                            -0.5f,  0.5f, 0.0f, 0.0f, 1.0f
                            };

        std::vector<unsigned int> indices = {0, 1, 3, 1, 2, 3};
        std::shared_ptr<VertexBuffer> vertexBuffer (VertexBuffer::create((float*) vertices.data(), sizeof(float) * vertices.size()));
        indexBuffer.reset(IndexBuffer::create(indices.data(), 6));
        vertexArray.reset(VertexArray::create());
        BufferLayout bf = 
        {
            { ShaderDataType::Float3, "pos" },
            { ShaderDataType::Float2, "texCoord"}
        };
        vertexArray->addBuffer(vertexBuffer, bf);

        shader.reset(Shader::create(FileUtils::readFile("shaders/default.vert.glsl"), FileUtils::readFile("shaders/default.frag.glsl")));
        texture.reset(Texture::create(TextureUtils::loadTexture("images/awesomeface.png")));
        shader->bind();
        shader->setMatrix4f("u_mvp", glm::mat4(1.0f));
        camera = OrthographicCamera(0, 960 * 2, 0, 540 * 2);
        texture.reset(Texture::create(TextureData(500, 500, ColorFormat(), 0xff0000ff)));
        texture1.reset(Texture::create(TextureData(500, 500, ColorFormat(), 0x0000fff0)));

        transform.scale = { 200.0f, 200.0f, 0.0f };
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    }

    void BaseLayer::onDetach()
    {

    }

    void BaseLayer::onUpdate(float delta)
    {
        drawImgui();
        shader->bind();
        shader->setMatrix4f("u_mvp", camera.getViewProjectionMatrix() * transform.getTransformMatrix());
        Render::getRenderer()->drawIndexed(*vertexArray, *indexBuffer, *shader, *texture);        
        shader->bind();
        shader->setMatrix4f("u_mvp", camera.getViewProjectionMatrix() * glm::translate(glm::mat4(1.0f), glm::vec3(400.0f, 400.0f, 0.0f)) * glm::scale(glm::mat4(1.0f), glm::vec3(200.0f, 200.0f, 1.0f)));
        Render::getRenderer()->drawIndexed(*vertexArray, *indexBuffer, *shader, *texture1);
    }

    void BaseLayer::drawImgui()
    {
        ImGui::Begin("Transform");
        ImGui::SliderFloat2("translation", &transform.position.x, 0, 600.0f);
        ImGui::SliderFloat("rotation", &transform.rotation.z, 0.0f, 360.0f);
        ImGui::SliderFloat2("scale", &transform.scale.x, 0.0f, 200.0f);

        std::vector<std::string> listbox_items { "images/awesomeface.png", "images/cat.png", "images/grass.png", "images/flower.jpg", "images/small_image.png" };
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

        std::vector<std::string> textures_items { "Linear", "Nearest"};
        if (ImGui::ListBoxHeader("Texture params", listbox_items.size()))
        {
            for (auto& item : textures_items)
            {
                if (ImGui::Selectable(item.c_str()))
                {
                    if (item == "Linear")
                    {
                        texture->setTextureFilter(Texture::TextureFilter::LINEAR);
                    }
                    else
                    {
                        texture->setTextureFilter(Texture::TextureFilter::NEAREST);
                    }
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
        if (ImGui::ListBoxHeader("Blend euation", equations.size()))
        {
            for (auto& item : equations)
            {
                if (ImGui::Selectable(item.c_str()))
                {
                    if (item == "GL_FUNC_ADD")
                    {
                        glBlendEquation(GL_FUNC_ADD);
                    }
                    else if (item == "GL_FUNC_SUBTRACT")
                    {
                        glBlendEquation(GL_FUNC_SUBTRACT);
                    }
                    else if (item == "GL_FUNC_REVERSE_SUBTRACT")
                    {
                        glBlendEquation(GL_FUNC_REVERSE_SUBTRACT);
                    }
                    else if (item == "GL_MIN")
                    {
                        glBlendEquation(GL_MIN);
                    }
                    else if (item == "GL_MAX")
                    {
                        glBlendEquation(GL_MAX);
                    }
                }
            }
            ImGui::ListBoxFooter();
        }
    }

    void BaseLayer::updateBlendFunc()
    {

    }

    void BaseLayer::onEvent(Event& e)
    {
        if (e.getEventType() == EventType::WindowResize)
        {
            const WindowResizeEvent& k = *(WindowResizeEvent*)&e;
            glViewport(0, 0, k.getWidth(), k.getHeight());
        }
        if (e.getEventType() == EventType::MouseScrolled)
        {
            const MouseScrollEvent& k = *(MouseScrollEvent*)&e;
            camera.zoom({k.getY() * 10.0f, k.getY() * 10.0f}, mousePos);
        }
        if (e.getEventType() == EventType::KeyPressed)
        {
            const KeyPressedEvent& k = *(KeyPressedEvent*)&e;
            int keycode = k.getKeyCode();
            
                if (keycode == 87)
                {
                    camera.move({0.0f, k.getRepeatCount() * 20.0f});
                }
                if (keycode == 83)
                {
                    camera.move({0.0f, -k.getRepeatCount() * 20.0f});
                }
                if (keycode == 68)
                {
                    camera.move({k.getRepeatCount() * 20.0f, 0.0f});
                }
                if (keycode == 65)
                {
                    camera.move({-k.getRepeatCount() * 20.0f, 0.0f});
                }
                if (keycode == 90)
                {
                    camera.move({0.0f, k.getRepeatCount() * 20.0f});
                }
                if (keycode == 88)
                {
                    camera.move({0.0f,-k.getRepeatCount() * 20.0f});
                }
                if (keycode == 69)
                {
                    camera.rotate(glm::radians(1.0f));
                }
                if (keycode == 81)
                {
                    camera.rotate(glm::radians(-1.0f));
                }
        }
    }
}