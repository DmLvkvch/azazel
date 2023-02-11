#pragma once

#include "renderer/rhi/gl/gl_headers.h"
#include <vector>
#include <string>

#include "renderer/Shader.h"
#include "renderer/VertexArray.h"
#include <memory>
#include "renderer/IndexBuffer.h"
#include "renderer/VertexBuffer.h"
#include "FileUtils.h"
#include <stb_image/stb_image.h>

namespace Azazel
{
    class CubeMap
    {
    public:
    std::unique_ptr<Shader> shader;
    std::unique_ptr<VertexArray> vertexArray;
    std::unique_ptr<IndexBuffer> indexBuffer;
    unsigned int textureID;
        CubeMap()
        {
            glGenTextures(1, &textureID);
            glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

            int width, height, nrChannels;
            std::vector<std::string> faces
            {
                "images/skybox/right.jpg",
                "images/skybox/left.jpg",
                "images/skybox/top.jpg",
                "images/skybox/bottom.jpg",
                "images/skybox/front.jpg",
                "images/skybox/back.jpg"
            };
            
            stbi_set_flip_vertically_on_load(false);

            for (unsigned int i = 0; i < faces.size(); i++)
            {
                unsigned char *data = stbi_load(faces[i].c_str(), &width, &height, &nrChannels, 4);
                if (data)
                {
                    glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 
                                0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data
                    );
                    stbi_image_free(data);
                }
                else
                {
                    std::cout << "Cubemap tex failed to load at path: " << faces[i] << std::endl;
                    stbi_image_free(data);
                }
            }
            glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
            shader.reset(Shader::create(FileUtils::readFile("shaders/skybox.vert.glsl"), FileUtils::readFile("shaders/skybox.frag.glsl")));

            float skyboxVertices[] = {
            // positions          
            -1.0f,  1.0f, -1.0f,
            -1.0f, -1.0f, -1.0f,
            1.0f, -1.0f, -1.0f,
            1.0f, -1.0f, -1.0f,
            1.0f,  1.0f, -1.0f,
            -1.0f,  1.0f, -1.0f,

            -1.0f, -1.0f,  1.0f,
            -1.0f, -1.0f, -1.0f,
            -1.0f,  1.0f, -1.0f,
            -1.0f,  1.0f, -1.0f,
            -1.0f,  1.0f,  1.0f,
            -1.0f, -1.0f,  1.0f,

            1.0f, -1.0f, -1.0f,
            1.0f, -1.0f,  1.0f,
            1.0f,  1.0f,  1.0f,
            1.0f,  1.0f,  1.0f,
            1.0f,  1.0f, -1.0f,
            1.0f, -1.0f, -1.0f,

            -1.0f, -1.0f,  1.0f,
            -1.0f,  1.0f,  1.0f,
            1.0f,  1.0f,  1.0f,
            1.0f,  1.0f,  1.0f,
            1.0f, -1.0f,  1.0f,
            -1.0f, -1.0f,  1.0f,

            -1.0f,  1.0f, -1.0f,
            1.0f,  1.0f, -1.0f,
            1.0f,  1.0f,  1.0f,
            1.0f,  1.0f,  1.0f,
            -1.0f,  1.0f,  1.0f,
            -1.0f,  1.0f, -1.0f,

            -1.0f, -1.0f, -1.0f,
            -1.0f, -1.0f,  1.0f,
            1.0f, -1.0f, -1.0f,
            1.0f, -1.0f, -1.0f,
            -1.0f, -1.0f,  1.0f,
            1.0f, -1.0f,  1.0f
        };

        std::shared_ptr<VertexBuffer> vb;
        vb.reset(VertexBuffer::create(skyboxVertices, sizeof(skyboxVertices)));
        std::vector<unsigned int> indices;
        for (int i = 0; i < sizeof(skyboxVertices) / 4 / 3; i++)
        {
            indices.push_back(i);
        }
        indexBuffer.reset(IndexBuffer::create(indices.data(), indices.size()));
        vertexArray.reset(VertexArray::create());
        vertexArray->addBuffer(vb, {{ShaderDataType::Float3, Semantic::Position3D}});
    }

    void draw()
    {
        float lightX = 1.0f * sin(glfwGetTime());
        float lightY = 0.3f;
        float lightZ = 1.0f * cos(glfwGetTime());
        glm::vec3 lightPos = glm::vec3(lightX, lightY, lightZ);
        glm::mat4 viewMatrix = glm::lookAt(lightPos, glm::vec3{0.0f, 0.0f, 0.0f}, glm::vec3{0.0f, 1.0f, 0.0f});
        glm::mat4 projectionMatrix = glm::perspective(glm::radians(45.0f), 1.5f, 0.1f, 100.0f);
        shader->bind();
        shader->setMatrix4f("projection", projectionMatrix);
        shader->setMatrix4f("view", viewMatrix);
        shader->setInt("skybox", 0);
        vertexArray->bind();
        indexBuffer->bind();
        glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
    }
    };
}