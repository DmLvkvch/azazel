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
        std::vector<float> vertices
        {
            -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 0.0f, 0.0f,  
             0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 0.0f, 1.0f,  
             0.5f, 0.5f,  -0.5f,  0.0f,  0.0f, -1.0f, 1.0f, 0.0f,  
             0.5f, 0.5f,  -0.5f,  0.0f,  0.0f, -1.0f, 1.0f, 0.0f,  
            -0.5f, 0.5f,  -0.5f,  0.0f,  0.0f, -1.0f, 0.0f, 1.0f,  
            -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 1.0f, 1.0f,  

            -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f, 0.0f, 0.0f,
             0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f, 0.0f, 1.0f,
             0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f, 1.0f, 0.0f,
             0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f, 1.0f, 0.0f,
            -0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f, 0.0f, 1.0f,
            -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f, 1.0f, 1.0f,

            -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f, 0.0f, 0.0f,
            -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f, 0.0f, 1.0f,
            -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f, 1.0f, 0.0f,
            -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f, 1.0f, 0.0f,
            -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f, 0.0f, 1.0f,
            -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f, 1.0f, 1.0f,

            0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f, 0.0f, 0.0f,
            0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f, 0.0f, 1.0f,
            0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f, 1.0f, 0.0f,
            0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f, 1.0f, 0.0f,
            0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f, 0.0f, 1.0f,
            0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f, 1.0f, 1.0f,

            -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f, 0.0f, 0.0f,
             0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f, 0.0f, 1.0f,
             0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f, 1.0f, 0.0f,
             0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f, 1.0f, 0.0f,
            -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f, 0.0f, 1.0f,
            -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f, 1.0f, 1.0f,

            -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f, 0.0f, 0.0f,
             0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f, 0.0f, 1.0f,
             0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f, 1.0f, 0.0f,
             0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f, 1.0f, 0.0f,
            -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f, 0.0f, 1.0f,
            -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f, 1.0f, 1.0f
        };

        std::vector<unsigned int> indices;
        for (int i = 0; i < vertices.size(); i++)
        {
            indices.push_back(i);
        }

        this->texture.reset(Texture::create(TextureData(500, 500, ColorFormat(), 0xaaff00ff)));

        //this->face.reset(Texture::create(TextureUtils::loadTexture("images/awesomeface.png")));
        this->face.reset(Texture::create(TextureData(4000, 4000, ColorFormat(), 0xaaff00ff)));
        face->setTextureFilter(Texture::TextureFilter::Linear);

        this->indexBuffer.reset(IndexBuffer::create(indices.data(), indices.size()));
        std::shared_ptr<VertexBuffer> vertexBuffer (VertexBuffer::create((float*) vertices.data(), sizeof(float) * vertices.size()));
        this->vertexArray.reset(VertexArray::create());
        BufferLayout vbo { { ShaderDataType::Float3, "position" }, { ShaderDataType::Float3, "normal" }, { ShaderDataType::Float2, "normal" } };
        vertexArray->addBuffer(vertexBuffer, vbo);

        shader.reset(Shader::create(FileUtils::readFile("shaders/solid.vert.glsl"), FileUtils::readFile("shaders/solid.frag.glsl")));

        gridShader.reset(Shader::create(FileUtils::readFile("shaders/grid.vert.glsl"), FileUtils::readFile("shaders/grid.frag.glsl")));
        
        std::vector<float> gridVerts
        {
            0.0f,   0.0f,  0.0f, 0.0f, 0.0f,
            0.0f,   50.0f, 0.0f, 1.0f, 0.0f,
            100.0f, 50.0f, 0.0f, 1.0f, 1.0f,
            100.0f, 0.0f,  0.0f, 0.0f, 1.0f
        };

        unsigned int gridInds[6] = {0, 1, 2, 0, 2, 3};

        gridIndexBuffer.reset(IndexBuffer::create(gridInds, 6));
        std::shared_ptr<VertexBuffer> vertexBuffer1 (VertexBuffer::create((float*) gridVerts.data(), sizeof(float) * gridVerts.size() * 5));

        gridVertexArray.reset(VertexArray::create());
        BufferLayout vbo11 = { { ShaderDataType::Float3, "positions" }, { ShaderDataType::Float2, "texCoord"} };
        gridVertexArray->addBuffer(vertexBuffer1, vbo11);

        orthographicCamera = OrthographicCamera(0, 7, 0, 5, -100.0f, 100.0f);
    }

    void GLLayer::onDetach()
    {

    }
    
    void GLLayer::onUpdate(float delta)
    {
        glm::mat4 mvp = orthographicCamera.getViewProjectionMatrix() * glm::scale(glm::mat4(1.0f), {0.1f, 0.1f, 0.1f});
        // gridShader->bind();
        // gridShader->setMatrix4f("u_mvp", mvp);
        // gridShader->setVec2f("iResolution", {1280, 720});
        // Render::getRenderer()->drawIndexed(*gridVertexArray, *gridIndexBuffer, *gridShader, *texture);

        mvp = orthographicCamera.getViewProjectionMatrix()  * glm::translate(glm::mat4(1.0f), glm::vec3{1.0f, 3.0f, 0.0f}) * glm::rotate(glm::mat4(1.0f), glm::radians((float) glfwGetTime()* 10.0f), {1.0f, 0.0f, 1.0f}) * glm::scale(glm::mat4(1.0f), {2.0f, 2.0f, 2.0f});
        Render::getRender()->setDepthTest(true);
        face->bind(0);
        shader->bind();
        shader->setInt("u_texture", 0);
        shader->setMatrix4f("u_mvp", mvp);
        Render::getRender()->drawIndexed(*vertexArray, *indexBuffer, *shader, *face);
        Render::getRender()->setDepthTest(false);

    }
    
    void GLLayer::onEvent(Event& e)
    {
    }
}