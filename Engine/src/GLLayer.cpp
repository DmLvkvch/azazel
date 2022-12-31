#include "GLLayer.h"
#define _CRTDBG_MAP_ALLOC

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

#include "TextureUtils.h"
#include "FileUtils.h"
#include "renderer/TextureData.h"
#include <renderer/Render.h>

namespace Azazel
{
    
    void GLLayer::onAttach()
    {
        float left =   1 * 200.0f;
        float top =    1 * 200.0f;
        float front =  1 * 200.0f;
        float bottom = 1 * 200.0f;
        float back =   1 * 200.0f;
        float right =  1 * 200.0f;

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

        std::vector<glm::vec3> vertices
        {

        };
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

        this->texture.reset(Texture::create(TextureData(500, 500, ColorFormat(), 0xaaff00ff)));

        this->face.reset(Texture::create(TextureData(500, 500, ColorFormat(), 0xaaff00ff)));

        this->indexBuffer.reset(IndexBuffer::create(indices.data(), indices.size()));
        // leak
        std::shared_ptr<VertexBuffer> vertexBuffer (VertexBuffer::create((float*)vertices.data(), sizeof(float) * vertices.size() * 3));
        std::shared_ptr<VertexBuffer> vertexBufferT (VertexBuffer::create((float*)texCoords.data(), sizeof(float) * texCoords.size() * 2));
        std::shared_ptr<VertexBuffer> vertexBufferN (VertexBuffer::create((float*)normals.data(), sizeof(float) * normals.size() * 3));
        this->vertexArray.reset(VertexArray::create());
        BufferLayout vbo = {{
            ShaderDataType::Float3, "position"
        }};
        vertexArray->addBuffer(vertexBuffer, vbo);
        BufferLayout vbo1 = {{ ShaderDataType::Float2, "texCoord" }};
        vertexArray->addBuffer(vertexBufferT, vbo1);
        BufferLayout vbo2 = {{ ShaderDataType::Float3, "normals" }};
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
        
        std::vector<float> gridVerts = 
        {
            0.0f,    0.0f, 0.0f,   0.0f, 0.0f,
            0.0f,    50.0f, 0.0f, 1.0f, 0.0f,
            100.0f, 50.0f, 0.0f, 1.0f, 1.0f,
            100.0f, 0.0f, 0.0f,   0.0f, 1.0f
        };

        unsigned int gridInds[6] = {0, 1, 2, 0, 2, 3};

        gridIndexBuffer.reset(IndexBuffer::create(gridInds, 6));
        std::shared_ptr<VertexBuffer> vertexBuffer1 (VertexBuffer::create((float*) gridVerts.data(), sizeof(float) * gridVerts.size() * 5));

        gridVertexArray.reset(VertexArray::create());
        BufferLayout vbo11 = { { ShaderDataType::Float3, "positions" }, { ShaderDataType::Float2, "texCoord"}};
        gridVertexArray->addBuffer(vertexBuffer1, vbo11);

        orthographicCamera = OrthographicCamera(0, 1200, 0, 700);
    }

    void GLLayer::onDetach()
    {

    }
    
    void GLLayer::onUpdate(float delta)
    {
        glm::vec3 lightPos {0.0f, 500.0f, 0.0f};
        glm::vec3 lightColor;
        lightColor.x = (float) glm::sin(glfwGetTime() * 2.0f + 0.2f);
        lightColor.y = (float) glm::sin(glfwGetTime() * 0.7f + 0.2f);
        lightColor.z = (float) glm::sin(glfwGetTime() * 1.3f  + 0.2f);
        
        glm::vec3 diffuseColor = lightColor   * glm::vec3(0.5f); 
        glm::vec3 ambientColor = diffuseColor * glm::vec3(0.2f); 

        glm::mat4 mvp = orthographicCamera.getViewProjectionMatrix()  * glm::mat4(1.0f);
        gridShader->bind();
        gridShader->setMatrix4f("u_mvp", mvp);
        Render::getRenderer()->drawIndexed(*gridVertexArray, *gridIndexBuffer, *gridShader, *texture);

        texture->bind();
        face->bind(1);
        shader->bind();
        shader->setMatrix4f("u_mvp", mvp);
        shader->setMatrix4f("u_model", glm::mat4(1.0f));        
        shader->setVec3f("light.ambient", ambientColor);
        shader->setVec3f("light.diffuse", diffuseColor)       ;        shader->setVec3f("u_lightPos", lightPos);
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
                    orthographicCamera.move({0.0f, k.getRepeatCount() * 10.0f});

                    break;
                }
                case 83:
                {
                    camera.moveForward(k.getRepeatCount() * 10.0f);
                    orthographicCamera.move({0.0f,-k.getRepeatCount() * 10.0f});

                    break;
                }
                case 68:
                {
                    camera.moveRight(k.getRepeatCount() * 10.0f);
                    orthographicCamera.move({k.getRepeatCount() * 10.0f, 0.0f});
                    break;
                }
                case 65:
                {
                    camera.moveRight(-k.getRepeatCount() * 10.0);
                    orthographicCamera.move({-k.getRepeatCount() * 10.0f, 0.0f});

                    break;
                }
                case 90:
                {
                    camera.moveUp(k.getRepeatCount() * 10.0f);

                    orthographicCamera.move({0.0f, k.getRepeatCount() * 10.0f});

                    break;
                }
                case 88:
                {
                    orthographicCamera.move({0.0f,-k.getRepeatCount() * 10.0f});
                    camera.moveUp(-k.getRepeatCount() * 10.0f);
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