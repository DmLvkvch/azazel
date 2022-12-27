#include "BaseLayer.h"

#include <TextureUtils.h>
#include <FileUtils.h>

#include <events/KeyEvent.h>
#include <events/MouseEvent.h>
#include <events/ApplicationEvent.h>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

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
        vertexBuffer.reset(VertexBuffer::create((float*) vertices.data(), sizeof(float) * vertices.size()));
        indexBuffer.reset(IndexBuffer::create(indices.data(), 6));
        vertexArray.reset(VertexArray::create());
        BufferLayout bf = 
        {
            { ShaderDataType::Float3, "pos" },
            { ShaderDataType::Float2, "texCoord"}
        };
        vertexArray->addBuffer(*vertexBuffer, bf);

        shader.reset(Shader::create(FileUtils::readFile("shaders/default.vert.glsl"), FileUtils::readFile("shaders/default.frag.glsl")));
        TextureData q = TextureUtils::loadTexture("images/awesomeface.png");
        texture.reset(Texture::create(q));
        shader->bind();
        shader->setMatrix4f("u_mvp", glm::mat4(1.0f));
        glEnable(GL_BLEND);  
        glBlendFunc(GL_SRC_ALPHA, GL_DST_ALPHA);
        glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ZERO);
    }

    void BaseLayer::onDetach()
    {

    }

    void BaseLayer::onUpdate(float delta)
    {
        drawImgui();
        texture->bind();
        shader->bind();
        shader->setMatrix4f("u_mvp", camera.getViewProjectionMatrix() * transform.getTransformMatrix());
        vertexArray->bind();
        indexBuffer->bind();
        glDrawElements(GL_TRIANGLES, indexBuffer->getElementCount() * sizeof(unsigned int), GL_UNSIGNED_INT, 0);
    }

    void BaseLayer::drawImgui()
    {
        // TODO
        static bool open = true;
        ImGui::Begin("Transform", &open);
        ImGui::SliderFloat2("translation", &transform.position.x, -1.0f, 1.0f);
        ImGui::SliderFloat("rotation", &transform.rotation.z, 0.0f, 360.0f);
        ImGui::SliderFloat2("scale", &transform.scale.x, 0.0f, 10.0f);

        std::vector<std::string> listbox_items { "images/awesomeface.png", "images/cat.png", "images/grass.png", "images/flower.jpg" };
        bool b = ImGui::ListBoxHeader("Textures", listbox_items.size());
        if (b)
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
        ImGui::End();
        // TODO

    }

    void BaseLayer::onEvent(Event& e)
    {
        std::cout<<getName()<<" "<<e.toString()<<std::endl;
        if (e.getEventType() == EventType::WindowResize)
        {
            const WindowResizeEvent& k = *(WindowResizeEvent*)&e;
            glViewport(0, 0, k.getWidth(), k.getHeight());
        }
        if (e.getEventType() == EventType::KeyPressed)
        {
           const KeyPressedEvent& k = *(KeyPressedEvent*)&e;
            switch(k.getKeyCode())
            {
                case 87:
                {
                    camera.move({0.0f, k.getRepeatCount() * 10.0f / 1000.0f});
                    break;
                }
                case 83:
                {
                    camera.move({0.0f,-k.getRepeatCount() * 10.0f / 1000.0f});
                    break;
                }
                case 68:
                {
                    camera.move({k.getRepeatCount() * 10.0f / 1000.0f, 0.0f});
                    break;
                }
                case 65:
                {
                    camera.move({-k.getRepeatCount() * 10.0f / 1000.0f, 0.0f});

                    break;
                }
                case 90:
                {
                    camera.move({0.0f, k.getRepeatCount() * 10.0f / 1000.0f});
                    break;
                }
                case 88:
                {
                    camera.move({0.0f,-k.getRepeatCount() * 10.0f / 1000.0f});
                    break;
                }
                case 69:
                {
                    camera.rotate(glm::radians(1.0f));
                    break;
                }
                case 81:
                {
                    camera.rotate(glm::radians(-1.0f));
                    break;
                }
            }
            std::cout<<k.getKeyCode()<<" keycode"<<std::endl;
        }
    }
}