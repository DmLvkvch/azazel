#include "TestLayer.h"

#include <vector>
#include "FileUtils.h"
#include "TextureUtils.h"
#include "events/KeyEvent.h"
#include "events/MouseEvent.h"
#include "events/ApplicationEvent.h"

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
        TextureData q = TextureUtils::loadTexture("images/awesomeface.png");
        texture1.reset(Texture::create(q));
        shader->bind();
        shader->setMatrix4f("u_mvp", glm::mat4(1.0f));
        glEnable(GL_BLEND);  
        glBlendFunc(GL_SRC_ALPHA, GL_DST_ALPHA);
        glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ZERO);
        camera = OrthographicCamera(-1, 1, -1, 1);
    }

    void TestLayer::onDetach()
    {

    }

    void TestLayer::onUpdate(float delta)
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClearColor(0.3f, 0.25f, 0.5f, 1.0f);
        texture1->bind();
        shader->bind();
        shader->setMatrix4f("u_mvp", camera.getViewProjectionMatrix());
        vertexArray->bind();
        indexBuffer->bind();
        glDrawElements(GL_TRIANGLES, indexBuffer->getElementCount() * sizeof(unsigned int), GL_UNSIGNED_INT, 0);

    }

    void TestLayer::onEvent(Event& e)
    {
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
            }
            std::cout<<k.getKeyCode()<<" keycode"<<std::endl;
        }
        if (e.getEventType() == EventType::MouseScrolled)
        {
            const MouseScrollEvent& k = *(MouseScrollEvent*)(Event*)&e;
        }
        if (e.getEventType() == EventType::MouseMoved)
        {
            const MouseMovedEvent& k = *(MouseMovedEvent*)(Event*)&e;
        }
    }
}