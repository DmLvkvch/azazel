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
#include "events/ApplicationEvent.h"

#include <vector>

#include "renderer/rhi/gl/GLESShader.h"
#include "renderer/rhi/gl/GLESTexture.h"
#include "renderer/rhi/gl/GLESVertexBuffer.h"
#include "renderer/rhi/gl/GLESIndexBuffer.h"
#include "renderer/rhi/gl/GLESVertexArray.h"
#include "renderer/rhi/gl/GLESVertexBufferLayout.h"
#include "renderer/VertexBuffer.h"

#include "TextureUtils.h"
#include "FileUtils.h"
#include "renderer/TextureData.h"

namespace Azazel
{

    
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
        
        TextureData td = TextureUtils::loadTexture("images/container2.png");

        this->texture.reset(Texture::create(td));

        td = TextureUtils::loadTexture("images/awesomeface.png");

        this->face.reset(Texture::create(td));

        this->indexBuffer.reset(IndexBuffer::create(indices.data(), indices.size()));
        GLESVertexBuffer vertexBuffer(vertices.data(), sizeof(float) * vertices.size() * 3);
        GLESVertexBuffer vertexBufferT(texCoords.data(), sizeof(float) * texCoords.size() * 2);
        GLESVertexBuffer vertexBufferN(normals.data(), sizeof(float) * normals.size() * 3);

        this->vertexArray.reset(VertexArray::create());
        GLESVertexBufferLayout vbo;
        vbo.addFloat(3);
        vertexArray->addBuffer(vertexBuffer, vbo);
        GLESVertexBufferLayout vbo1;
        vbo1.addFloat (2);
        vertexArray->addBuffer(vertexBufferT, vbo1);
        GLESVertexBufferLayout vbo2;
        vbo2.addFloat (3);
        vertexArray->addBuffer(vertexBufferN, vbo2);

        std::string vertCode = FileUtils::readFile("shaders/light/specular.light.vert.glsl");

        std::string fragCode = FileUtils::readFile("shaders/light/specular.light.frag.glsl");

        shader.reset(Shader::create(vertCode, fragCode));
        shader->bind();
        shader->setInt("u_texture_0", 0);
        shader->setInt("face", 1);

        shader->setVec3f("material.ambient", 1.0f, 0.5f, 0.31f);
        shader->setVec3f("material.diffuse", 1.0f, 0.5f, 0.31f);
        shader->setVec3f("material.specular", 0.5f, 0.5f, 0.5f);
        shader->setFloat("material.shininess", 32.0f);
        shader->setVec3f("light.ambient",  0.2f, 0.2f, 0.2f);
        shader->setVec3f("light.diffuse",  0.5f, 0.5f, 0.5f);
        shader->setVec3f("light.specular", 1.0f, 1.0f, 1.0f); 

        gridShader.reset(Shader::create(FileUtils::readFile("shaders/grid.vert.glsl"), FileUtils::readFile("shaders/grid.frag.glsl")));
        std::vector<glm::vec3> gridVerts;
        gridVerts.push_back(glm::vec3(0.0f, 0.0f, 0.0f));
        gridVerts.push_back(glm::vec3(0.0f, 0.0f, 500.0f));
        gridVerts.push_back(glm::vec3(1000.0f, 0.0f, 500.0f));
        gridVerts.push_back(glm::vec3(1000.0f, 0.0f, 0.0f));
        std::vector<glm::vec2> gridTexCoords;
        gridTexCoords.push_back(glm::vec2(0.0, 0.0));
        gridTexCoords.push_back(glm::vec2(1.0, 0.0));
        gridTexCoords.push_back(glm::vec2(1.0, 1.0));
        gridTexCoords.push_back(glm::vec2(0.0, 1.0));

        unsigned int gridInds[6] = {0, 1, 2, 0, 2, 3};

        this->gridIndexBuffer.reset(IndexBuffer::create(gridInds, 6));
        GLESVertexBuffer vertexBuffer1(gridVerts.data(), sizeof(float) * vertices.size() * 3);
        GLESVertexBuffer vertexBufferT1(gridTexCoords.data(), sizeof(float) * texCoords.size() * 2);

        this->gridVertexArray.reset(VertexArray::create());
        GLESVertexBufferLayout vbo11;
        vbo11.addFloat(3);
        gridVertexArray->addBuffer(vertexBuffer1, vbo11);
        GLESVertexBufferLayout vbo111;
        vbo111.addFloat(2);
        gridVertexArray->addBuffer(vertexBufferT1, vbo111);

        glm::vec3 camPos = glm::vec3(0.0f, 500.0f, 1500.0f);
        camera.setPosition(camPos);

        glEnable(GL_DEPTH_TEST);
        // glEnable(GL_CULL_FACE);
        // glCullFace(GL_BACK);
        // glFrontFace( GL_CCW );
        BufferLayout bl = {
            { ShaderDataType::Float3, "position" },
            { ShaderDataType::Float3, "normal" },
            { ShaderDataType::Float2, "texCoord" }
        };
        this->fb.reset(Texture::create(400, 400, 0xff00ff00));
        this->frameBuffer.reset(FrameBuffer::create(fb.get(), nullptr));
        // glEnable(GL_BLEND);
        // glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);  
        // glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ZERO);
    }

    void GLLayer::onDetach()
    {

    }
    
    void GLLayer::onUpdate()
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
        glm::vec3 lightPos {0.0f, 500.0f, 0.0f};
        glm::vec3 lightColor;
        lightColor.x = glm::sin(glfwGetTime() * 2.0f + 0.2f);
        lightColor.y = glm::sin(glfwGetTime() * 0.7f + 0.2f);
        lightColor.z = glm::sin(glfwGetTime() * 1.3f  + 0.2f);
        
        glm::vec3 diffuseColor = lightColor   * glm::vec3(0.5f); 
        glm::vec3 ambientColor = diffuseColor * glm::vec3(0.2f); 
        
        glm::vec3 rotation{};
        glm::mat4 projection = glm::perspective(glm::radians(45.0f), 1.5f, 0.1f, 5000.0f);
        glm::vec3 scale {1.0f, 1.0f, 1.0f};

        glm::mat4 rotX = glm::rotate(glm::mat4(1.0f), glm::radians(rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
        glm::mat4 rotZ = glm::rotate(glm::mat4(1.0f), glm::radians(rotation.x), glm::vec3(0.0f, 0.0f, 1.0f));
        glm::mat4 rotY = glm::rotate(glm::mat4(1.0f), glm::radians(rotation.x), glm::vec3(0.0f, 1.0f, 0.0f));

        glm::mat4 model = glm::scale(glm::mat4(1.0f), scale) * rotX * rotY * rotZ;

        glm::mat4 mvp = projection * camera.getViewLookAtMatrix()  * model;
        gridShader->bind();
        gridShader->setMatrix4f("u_mvp", mvp);
        gridVertexArray->bind();
        gridIndexBuffer->bind();
        glDrawElements(GL_TRIANGLES, gridIndexBuffer->getElementCount() * sizeof(unsigned int), GL_UNSIGNED_INT, 0);

        texture->bind();
        face->bind(1);
        shader->bind();
        glm::mat4 mvp2 = projection * camera.getViewLookAtMatrix()  * glm::scale(glm::mat4(1.0f), glm::vec3(10.0f, 10.0f, 10.0f)) * model;
        shader->setMatrix4f("u_mvp", mvp);
        shader->setMatrix4f("u_model", model);        
        shader->setVec3f("light.ambient", ambientColor);
        shader->setVec3f("light.diffuse", diffuseColor);

        shader->setVec3f("u_lightPos", lightPos);
        vertexArray->bind();
        indexBuffer->bind();
        glDrawElements(GL_TRIANGLES, indexBuffer->getElementCount() * sizeof(unsigned int), GL_UNSIGNED_INT, 0);

    }
    
    void GLLayer::onEvent(Event& e)
    {
        std::cout<<e.toString()<<std::endl;
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
                    camera.moveForward(-k.getRepeatCount() * 10.0f);
                    break;
                }
                case 83:
                {
                    camera.moveForward(k.getRepeatCount() * 10.0f);
                    break;
                }
                case 68:
                {
                    camera.moveRight(k.getRepeatCount() * 10.0f);
                    break;
                }
                case 65:
                {
                    camera.moveRight(-k.getRepeatCount() * 10.0);
                    break;
                }
                case 90:
                {
                    camera.moveUp(k.getRepeatCount() * 10.0f);
                    break;
                }
                case 88:
                {
                    camera.moveUp(k.getRepeatCount() * -10.0f);
                    break;
                }
            }
            std::cout<<k.getKeyCode()<<" keycode"<<std::endl;
        }
        if (e.getEventType() == EventType::MouseScrolled)
        {
             const MouseScrollEvent& k = *(MouseScrollEvent*)(Event*)&e;

            glm::vec3 dir = glm::normalize(-camera.getPosition() - glm::vec3(0.0, 0.0, 0.0)) * 10.0f * k.getY();
            camera.move(dir);
        }
        if (e.getEventType() == EventType::MouseMoved)
        {
            const MouseMovedEvent& k = *(MouseMovedEvent*)(Event*)&e;
        }
    }
}