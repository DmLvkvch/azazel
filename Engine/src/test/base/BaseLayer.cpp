#include "BaseLayer.h"

#include "TextureUtils.h"
#include "api/file/FileUtils.h"
#include "render/Render.h"
#include "render/Mesh.h"
#include "resources/ResourceManager.h"

namespace Azazel
{
    void BaseLayer::onAttach()
    {
        std::vector<Vertex_P3_C4_T2> vertices;
        
        vertices.emplace_back(glm::vec3{-0.5f, -0.5f, 0.0f}, glm::vec4{1.0f, 0.0f, 0.0f, 1.0f}, glm::vec2{1.0f, 1.0f});
        vertices.emplace_back(glm::vec3{-0.5f,  0.5f, 0.0f}, glm::vec4{1.0f, 0.0f, 0.0f, 1.0f}, glm::vec2{1.0f, 0.0f});
        vertices.emplace_back(glm::vec3{ 0.5f,  0.5f, 0.0f}, glm::vec4{1.0f, 0.0f, 0.0f, 1.0f}, glm::vec2{0.0f, 0.0f});
        vertices.emplace_back(glm::vec3{ 0.5f, -0.5f, 0.0f}, glm::vec4{1.0f, 0.0f, 0.0f, 1.0f}, glm::vec2{0.0f, 1.0f});

        std::vector<unsigned int> indices {0, 1, 2, 0, 2, 3};

        std::shared_ptr<VertexBuffer> vertexBuffer (VertexBuffer::create((float*) vertices.data(), vertices.size() * sizeof(Vertex_P3_C4_T2)));
        indexBuffer.reset(IndexBuffer::create(indices.data(), indices.size()));
        vertexArray.reset(VertexArray::create());
        vertexArray->addBuffer(vertexBuffer, Vertex_P3_C4_T2::bufferLayout);

        shader.reset(Shader::create(FileUtils::readFile("shaders/default.vert.glsl"), FileUtils::readFile("shaders/default.frag.glsl")));
        camera = OrthographicCamera(0, 960, 0, 540);
        TextureData square1(500, 500, 0xff0000ff); 
        texture.reset(Texture::create(square1));
        delete[] square1.data;

        TextureData square2(500, 500, 0x0000fff0);
        texture1.reset(Texture::create(square2));
        delete[] square2.data;

        transform.scale = { 100.0f, 100.0f, 0.0f };
        color = {0.0f, 0.0f, 0.0f, 1.0f};
        mesh = Mesh<Vertex_P3_C4_T2>(vertices, indices);
        
    }

    void BaseLayer::onDetach()
    {

    }

    void BaseLayer::onUpdate(float delta)
    {
    }

    void BaseLayer::onRender(float delta)
    {
        Render::getRender()->setBlend(true);
        Render::getRender()->setBlendFunc(BlendFunction::SRC_ALPHA, BlendFunction::ONE_MINUS_SRC_ALPHA);

        shader->bind();
        shader->setMatrix4f("u_mvp", camera.getViewProjectionMatrix() * transform.getTransformMatrix());
        Render::getRender()->drawMesh<Vertex_P3_C4_T2>(mesh, *shader, *texture);

        shader->bind();
        shader->setMatrix4f("u_mvp", camera.getViewProjectionMatrix() * glm::translate(glm::mat4(1.0f), glm::vec3(400.0f, 400.0f, 0.0f)) * glm::scale(glm::mat4(1.0f), glm::vec3(200.0f, 200.0f, 1.0f)));
        Render::getRender()->drawIndexed(*vertexArray, *indexBuffer, *shader);
    }

    void BaseLayer::onImguiRender(float delta)
    {
        drawImgui(delta);
    }

    void BaseLayer::drawImgui(float delta)
    {
        ImGui::Begin("Transform");
     
        ImGui::Text("FPS %.3f", 1000.0f / delta);

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
                        Render::getRender()->setBlendEquation(BlendEquation::ADD);
                    }
                    else if (item == "GL_FUNC_SUBTRACT")
                    {
                        Render::getRender()->setBlendEquation(BlendEquation::SUBTRACT);
                    }
                    else if (item == "GL_FUNC_REVERSE_SUBTRACT")
                    {
                        Render::getRender()->setBlendEquation(BlendEquation::REVERSE_SUBTRACT);
                    }
                    else if (item == "GL_MIN")
                    {
                        Render::getRender()->setBlendEquation(BlendEquation::MIN);
                    }
                    else if (item == "GL_MAX")
                    {
                        Render::getRender()->setBlendEquation(BlendEquation::MAX);
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