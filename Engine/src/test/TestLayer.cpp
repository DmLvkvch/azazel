#include "TestLayer.h"

#include <vector>
#include "api/file/FileUtils.h"
#include "TextureUtils.h"
#include "events/KeyEvent.h"
#include "events/MouseEvent.h"
#include "events/ApplicationEvent.h"
#include "IO/Input.h"
#include "render/Render.h"


namespace Azazel
{
    void TestLayer::onAttach()
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
        vertexArray->addBuffer(vertexBuffer, Vertex_P3_T2::bufferLayout);

        shader.reset(Shader::create(FileUtils::readFile("shaders/default.vert.glsl"), FileUtils::readFile("shaders/default.frag.glsl")));
        auto textureData = TextureUtils::loadTexture("images/awesomeface.png");
        texture.reset(Texture::create(textureData));
        TextureUtils::freeTextureData(textureData);

        shader->bind();
        shader->setMatrix4f("u_mvp", glm::mat4(1.0f));
        camera = OrthographicCamera(940, 560);
    }

    void TestLayer::onDetach()
    {

    }

    void TestLayer::onInputUpdate(float delta)
    {

    }

    void TestLayer::onUpdate(float delta)
    {
        shader->bind();
        shader->setMatrix4f("u_mvp", camera.getViewProjectionMatrix() * glm::scale(glm::mat4(1.0f), glm::vec3(100.0f, 100.0f, 0.0f)));
        Render::getRender()->drawIndexed(*vertexArray, *indexBuffer, *shader);
    }

    void TestLayer::onEvent(Event& e)
    {
        
    }
}