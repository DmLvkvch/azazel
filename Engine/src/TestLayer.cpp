#include "TestLayer.h"

#include <vector>
#include "FileUtils.h"
#include "TextureUtils.h"
#include "events/KeyEvent.h"
#include "events/MouseEvent.h"
#include "events/ApplicationEvent.h"

#include <Input.h>
#include <renderer/Render.h>

namespace Azazel
{
    void TestLayer::onAttach()
    {
        std::vector<float> vertices = {
                    0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
                    0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
                    -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
                    -0.5f,  0.5f, 0.0f, 0.0f, 1.0f
         };

        std::vector<unsigned int> indices = {0, 1, 3, 1, 2, 3};
        VertexBuffer* vertexBuffer = VertexBuffer::create((float*) vertices.data(), sizeof(float) * vertices.size());
        indexBuffer.reset(IndexBuffer::create(indices.data(), 6));
        vertexArray.reset(VertexArray::create());
        BufferLayout bf = 
        {
            { ShaderDataType::Float3, "pos" },
            { ShaderDataType::Float2, "texCoord"}
        };
        vertexArray->addBuffer(*vertexBuffer, bf);

        shader.reset(Shader::create(FileUtils::readFile("shaders/default.vert.glsl"), FileUtils::readFile("shaders/default.frag.glsl")));
        texture1.reset(Texture::create(TextureUtils::loadTexture("images/awesomeface.png")));
        texture2.reset(Texture::create(TextureData(500, 500, ColorFormat(), 0xff00ffff)));

        shader->bind();
        shader->setMatrix4f("u_mvp", glm::mat4(1.0f));
        camera = OrthographicCamera(0, 940, 0, 560);
    }

    void TestLayer::onDetach()
    {

    }

    void TestLayer::onUpdate(float delta)
    {
        shader->bind();
        shader->setMatrix4f("u_mvp", camera.getViewProjectionMatrix() * glm::scale(glm::mat4(1.0f), glm::vec3(200.0f, 200.0f, 0.0f)));
        Render::getRenderer()->drawIndexed(*vertexArray, *indexBuffer, *shader, *texture1);
        if (Input::getInput()->isKeyPressed(65))
        {
            camera.move({ -1.0f, 0.0f });
        }
        if (Input::getInput()->isKeyPressed(68))
        {
            camera.move({ 1.0f, 0.0f });
        }
    }

    void TestLayer::onEvent(Event& e)
    {
        
    }
}