#include "GLLayer.h"

#include "renderer/rhi/gl/gl_headers.h"
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtx/normal.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/matrix_clip_space.hpp>

#include <iostream>
#include <fstream>
#include <streambuf>

#include "events/KeyEvent.h"
#include "events/MouseEvent.h"

#include <vector>

#include "renderer/rhi/gl/GLESShader.h"
#include "renderer/rhi/gl/GLESTexture.h"
#include "renderer/rhi/gl/GLESVertexBuffer.h"
#include "renderer/rhi/gl/GLESIndexBuffer.h"
#include "renderer/rhi/gl/GLESVertexArray.h"
#include "renderer/rhi/gl/GLESVertexBufferLayout.h"

namespace Azazel
{
    std::string readFile(const std::string& file)
    {
        std::fstream stream (file);
        if (!stream.is_open()) {
            std::cout << "Could not open the file - '" << file << "'" << std::endl;
        }
        return std::string((std::istreambuf_iterator<char>(stream)), std::istreambuf_iterator<char>());
    }
    
    void GLLayer::onAttach()
    {
        float left = 1 * 200.0f;
        float top = 1 * 200.0f;
        float front = 1 * 200.0f;
        float bottom = 1 * 200.0f;
        float back = 1 * 200.0f;
        float right = 1 * 200.0f;

        std::vector<glm::vec3> positions = {
            glm::vec3(-left, top, front),
            glm::vec3(-left, -bottom, front),
            glm::vec3(-left, top, -back),
            glm::vec3(-left, -bottom, -back),
            glm::vec3(right, top, front),
            glm::vec3(right, -bottom, front),
            glm::vec3(right, top, -back),
            glm::vec3(right, -bottom, -back),
        };

        std::vector<glm::vec3> vertices;
        vertices.push_back(positions[4]);
        vertices.push_back(positions[2]);
        vertices.push_back(positions[0]);
        vertices.push_back(positions[2]);
        vertices.push_back(positions[7]);
        vertices.push_back(positions[3]);
        vertices.push_back(positions[6]);
        vertices.push_back(positions[5]);
        vertices.push_back(positions[7]);
        vertices.push_back(positions[1]);
        vertices.push_back(positions[7]);
        vertices.push_back(positions[5]);
        vertices.push_back(positions[0]);
        vertices.push_back(positions[3]);
        vertices.push_back(positions[1]);
        vertices.push_back(positions[4]);
        vertices.push_back(positions[1]);
        vertices.push_back(positions[5]);
        vertices.push_back(positions[4]);
        vertices.push_back(positions[6]);
        vertices.push_back(positions[2]);
        vertices.push_back(positions[2]);
        vertices.push_back(positions[6]);
        vertices.push_back(positions[7]);
        vertices.push_back(positions[6]);
        vertices.push_back(positions[4]);
        vertices.push_back(positions[5]);
        vertices.push_back(positions[1]);
        vertices.push_back(positions[3]);
        vertices.push_back(positions[7]);
        vertices.push_back(positions[0]);
        vertices.push_back(positions[2]);
        vertices.push_back(positions[3]);
        vertices.push_back(positions[4]);
        vertices.push_back(positions[0]);
        vertices.push_back(positions[1]);

        std::vector<glm::vec2> texCoords;

        texCoords.push_back(glm::vec2(1.0f, 0.0f));
        texCoords.push_back(glm::vec2(0.0f, 1.0f));
        texCoords.push_back(glm::vec2(0.0f, 0.0f));
        texCoords.push_back(glm::vec2(1.0f, 1.0f));
        texCoords.push_back(glm::vec2(0.0f, 0.0f));
        texCoords.push_back(glm::vec2(1.0f, 0.0f));
        texCoords.push_back(glm::vec2(1.0f, 1.0f));
        texCoords.push_back(glm::vec2(0.0f, 0.0f));
        texCoords.push_back(glm::vec2(1.0f, 0.0f));
        texCoords.push_back(glm::vec2(0.0f, 1.0f));
        texCoords.push_back(glm::vec2(1.0f, 0.0f));
        texCoords.push_back(glm::vec2(1.0f, 1.0f));
        texCoords.push_back(glm::vec2(1.0f, 1.0f));
        texCoords.push_back(glm::vec2(0.0f, 0.0f));
        texCoords.push_back(glm::vec2(1.0f, 0.0f));
        texCoords.push_back(glm::vec2(1.0f, 1.0f));
        texCoords.push_back(glm::vec2(0.0f, 0.0f));
        texCoords.push_back(glm::vec2(1.0f, 0.0f));
        texCoords.push_back(glm::vec2(1.0f, 0.0f));
        texCoords.push_back(glm::vec2(1.0f, 1.0f));
        texCoords.push_back(glm::vec2(0.0f, 1.0f));
        texCoords.push_back(glm::vec2(1.0f, 1.0f));
        texCoords.push_back(glm::vec2(0.0f, 1.0f));
        texCoords.push_back(glm::vec2(0.0f, 0.0f));
        texCoords.push_back(glm::vec2(1.0f, 1.0f));
        texCoords.push_back(glm::vec2(0.0f, 1.0f));
        texCoords.push_back(glm::vec2(0.0f, 0.0f));
        texCoords.push_back(glm::vec2(0.0f, 1.0f));
        texCoords.push_back(glm::vec2(0.0f, 0.0f));
        texCoords.push_back(glm::vec2(1.0f, 0.0f));
        texCoords.push_back(glm::vec2(1.0f, 1.0f));
        texCoords.push_back(glm::vec2(0.0f, 1.0f));
        texCoords.push_back(glm::vec2(0.0f, 0.0f));
        texCoords.push_back(glm::vec2(1.0f, 1.0f));
        texCoords.push_back(glm::vec2(0.0f, 1.0f));
        texCoords.push_back(glm::vec2(0.0f, 0.0f));


        std::vector<glm::vec3> normals;

        for (int i = 0; i < vertices.size(); i+=3)
        {
            glm::vec3& p1 = vertices[i + 0];
            glm::vec3& p2 = vertices[i + 1];
            glm::vec3& p3 = vertices[i + 2];
            glm::vec3 normal = glm::triangleNormal(p1, p2, p3);
            normals.push_back(normal);
            normals.push_back(normal);
            normals.push_back(normal);
        }

        std::vector<unsigned int> indices;
        for (int i = 0; i < vertices.size(); i++)
        {
            indices.push_back(i);
        }

        this->texture = new GLESTexture("images/cat.png");

        VertexBuffer buffer = VertexBuffer::create(vertices.data(), sizeof(float) * vertices.size() * 3);
        buffer.bind();

        this->indexBuffer = new GLESIndexBuffer(indices.data(), indices.size());
        GLESVertexBuffer vertexBuffer(vertices.data(), sizeof(float) * vertices.size() * 3);
        GLESVertexBuffer vertexBufferT(texCoords.data(), sizeof(float) * texCoords.size() * 2);
        GLESVertexBuffer vertexBufferN(normals.data(), sizeof(float) * normals.size() * 3);
        glfwSwapInterval(1);

        this->vertexArray = new GLESVertexArray();
        GLESVertexBufferLayout vbo;
        vbo.add<float> (3);
        vertexArray->addBuffer(vertexBuffer, vbo);
        GLESVertexBufferLayout vbo1;
        vbo1.add<float> (2);
        vertexArray->addBuffer(vertexBufferT, vbo1, 1);
        GLESVertexBufferLayout vbo2;
        vbo2.add<float> (3);
        vertexArray->addBuffer(vertexBufferN, vbo2, 2);

        std::string vertCode = readFile("shaders/default.vert.glsl");

        std::string fragCode = readFile("shaders/default.frag.glsl");

        shader = new GLESShader(vertCode, fragCode);
        shader->bind();
        shader->setUniform1i("u_texture_0", 0);

        glEnable(GL_DEPTH_TEST);
        glEnable(GL_CULL_FACE);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ZERO);
    }

    void GLLayer::onDetach()
    {

    }
    
    void GLLayer::onUpdate()
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
        glm::vec3 lightPos {0.0f, 0.0f, 500.0f};
        shader->setVec3f("u_lightPos", lightPos);
        glm::vec3 rotation{};
        glm::mat4 projection = glm::perspective(glm::radians(60.0f), 1.5f, 0.1f, 2000.0f);
        glm::vec3 scale {1.0f, 1.0f, 1.0f};

        
        glm::vec3 camPos = glm::vec3(0.0f, 0.0f, 1000.0f);
        glm::mat4 view = glm::lookAt(camPos, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        glm::mat4 rotX = glm::rotate(glm::mat4(1.0f), glm::radians(rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
        glm::mat4 rotZ = glm::rotate(glm::mat4(1.0f), glm::radians(rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
        glm::mat4 rotY = glm::rotate(glm::mat4(1.0f), glm::radians(rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));

        glm::mat4 model = glm::scale(glm::mat4(1.0f), scale) * rotX * rotY * rotZ * glm::translate(glm::mat4(1.0f), camera.getPosition());

        glm::mat4 mvp = projection * camera.getViewLookAtMatrix(glm::vec3(0.0f, 1.0f, 0.0f)) * model;

        shader->setMatrix4f("u_mvp", mvp);
        shader->setMatrix4f("u_model", model);

        texture->bind();
        vertexArray->bind();
        indexBuffer->bind();
        glDrawElements(GL_TRIANGLES, indexBuffer->getElementCount() * sizeof(unsigned int), GL_UNSIGNED_INT, 0);
    }
    
    void GLLayer::onEvent(Event& e)
    {
        std::cout<<e.toString()<<std::endl;
        if (e.getEventType() == EventType::KeyPressed)
        {
            Event *tmp = (Event*)&e;
            KeyPressedEvent* k = (KeyPressedEvent*)tmp;
            switch(k->getKeyCode())
            {
                case 87:
                {
                    camera.moveForward(k->getRepeatCount() * 10.0f);
                    break;
                }
                case 83:
                {
                    camera.moveForward(k->getRepeatCount() * -10.0f);
                    break;
                }
                case 68:
                {
                    camera.moveRight(k->getRepeatCount() * 10.0f);
                    break;
                }
                case 65:
                {
                    camera.moveRight(k->getRepeatCount() * -10.0);
                    break;
                }
                case 90:
                {
                    camera.moveUp(k->getRepeatCount() * 10.0f);
                    break;
                }
                case 88:
                {
                    camera.moveUp(k->getRepeatCount() * -10.0f);
                    break;
                }
            }
            std::cout<<k->getKeyCode()<<" keycode"<<std::endl;
        }

        if (e.getEventType() == EventType::MousePressed)
        {
            Event *tmp = (Event*)&e;
            MouseMovedEvent* k = (MouseMovedEvent*)tmp;
        }
    }
}