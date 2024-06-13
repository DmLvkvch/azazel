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
        
        vertices.emplace_back(glm::vec3{-1.0f, -1.0f, 0.0f}, glm::vec4{1.0f, 0.0f, 0.0f, 1.0f}, glm::vec2{1.0f, 1.0f});
        vertices.emplace_back(glm::vec3{-1.0f,  1.0f, 0.0f}, glm::vec4{1.0f, 0.0f, 0.0f, 1.0f}, glm::vec2{1.0f, 0.0f});
        vertices.emplace_back(glm::vec3{ 1.0f,  1.0f, 0.0f}, glm::vec4{1.0f, 0.0f, 0.0f, 1.0f}, glm::vec2{0.0f, 0.0f});
        vertices.emplace_back(glm::vec3{ 1.0f, -1.0f, 0.0f}, glm::vec4{1.0f, 0.0f, 0.0f, 1.0f}, glm::vec2{0.0f, 1.0f});

        std::vector<unsigned int> indices {0, 1, 2, 0, 2, 3};

        std::shared_ptr<VertexBuffer> vertexBuffer (VertexBuffer::create((float*) vertices.data(), vertices.size() * sizeof(Vertex_P3_C4_T2)));
        indexBuffer.reset(IndexBuffer::create(indices.data(), indices.size()));
        vertexArray.reset(VertexArray::create());
        vertexArray->addBuffer(vertexBuffer, Vertex_P3_C4_T2::bufferLayout);

        shader.reset(Shader::create(FileUtils::readFile("shaders/default.vert.glsl"), FileUtils::readFile("shaders/default.frag.glsl")));
        
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
        Render::getRender()->setDepthTest(false);
        Render::getRender()->setBlendFunc(BlendFunction::SRC_ALPHA, BlendFunction::ONE_MINUS_SRC_ALPHA);

        shader->bind();
        Render::getRender()->drawIndexed(*vertexArray, *indexBuffer, *shader);
    }

    void BaseLayer::onImguiRender(float delta)
    {
    }

    void BaseLayer::drawImgui(float delta)
    {

    }

    void BaseLayer::updateBlendEquation()
    {

    }

    void BaseLayer::onEvent(Event& e)
    {
    }
}
