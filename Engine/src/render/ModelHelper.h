#pragma once

#include "Model.h"
#include "TextureUtils.h"

namespace Azazel
{
    class ModelHelper
    {
    public:
        static Model floor()
        {
            std::vector<float> vertices 
            {
                0.0f, 0.0f, 0.0f,  0.0f, 1.0f, 0.0f,  1.0f, 0.0f,
                10.0f, 0.0f, 0.0f,  0.0f, 1.0f, 0.0f,  0.0f, 0.0f,
                0.0f, 10.0f, 0.0f,  0.0f, 1.0f, 0.0f,  0.0f, 1.0f,
                10.0f, 10.0f, 0.0f,  0.0f, 1.0f, 0.0f,  1.0f, 1.0f
            };

            std::vector<unsigned int> indices
            {
                0, 1, 3, 3, 2, 0
            };
            Mesh mesh = Mesh::createMesh<Vertex_P3_N3_T2> (vertices, indices);
            auto textureData = TextureUtils::loadTexture("textures/wood.png");
            auto texture = Texture::create(textureData);
            TextureUtils::freeTextureData(textureData);

            mesh.textures.push_back(std::shared_ptr<Texture>(texture));

            mesh.material = Material();
            mesh.material->setProperty("u_texture_0", {MaterialProperty::TEXTURE, std::shared_ptr<Texture>(texture)});

            auto model = Model(mesh);

           // model.transform.scale = { 10.0f, 10.0f, 1.0f };
            model.transform.rotation.x = -90.0f;
            model.transform.position.x = -10.0f;
            model.transform.position.z = 10.0f;
            
            return model;
        }

        static Model cube()
        {
            std::vector<float> vertices
            {
                -0.5f, -0.5f, -0.5f,     0.0f,  0.0f, -1.0f,    0.0f, 0.0f,
                0.5f, -0.5f, -0.5f,     0.0f,  0.0f, -1.0f,    1.0f, 0.0f, 
                0.5f, 0.5f,  -0.5f,     0.0f,  0.0f, -1.0f,    1.0f, 1.0f, 
                0.5f, 0.5f,  -0.5f,     0.0f,  0.0f, -1.0f,    1.0f, 1.0f, 
                -0.5f, 0.5f,  -0.5f,     0.0f,  0.0f, -1.0f,    0.0f, 1.0f,
                -0.5f, -0.5f, -0.5f,     0.0f,  0.0f, -1.0f,    0.0f, 0.0f,
                                                                              
                -0.5f, -0.5f,  0.5f,     0.0f,  0.0f, 1.0f,     0.0f, 0.0f,
                0.5f, -0.5f,  0.5f,     0.0f,  0.0f, 1.0f,     1.0f, 0.0f, 
                0.5f,  0.5f,  0.5f,     0.0f,  0.0f, 1.0f,     1.0f, 1.0f, 
                0.5f,  0.5f,  0.5f,     0.0f,  0.0f, 1.0f,     1.0f, 1.0f, 
                -0.5f,  0.5f,  0.5f,     0.0f,  0.0f, 1.0f,     0.0f, 1.0f,
                -0.5f, -0.5f,  0.5f,     0.0f,  0.0f, 1.0f,     0.0f, 0.0f,
                                                                           
                -0.5f,  0.5f,  0.5f,     -1.0f,  0.0f, 0.0f,    0.0f, 0.0f,
                -0.5f,  0.5f, -0.5f,     -1.0f,  0.0f, 0.0f,    1.0f, 0.0f,
                -0.5f, -0.5f, -0.5f,     -1.0f,  0.0f, 0.0f,    1.0f, 1.0f,
                -0.5f, -0.5f, -0.5f,     -1.0f,  0.0f, 0.0f,    1.0f, 1.0f,
                -0.5f, -0.5f,  0.5f,     -1.0f,  0.0f, 0.0f,    0.0f, 1.0f,
                -0.5f,  0.5f,  0.5f,     -1.0f,  0.0f, 0.0f,    0.0f, 0.0f,
                                                                           
                0.5f,  0.5f,  0.5f,      1.0f,  0.0f,  0.0f,    0.0f, 0.0f,
                0.5f,  0.5f, -0.5f,      1.0f,  0.0f,  0.0f,    1.0f, 0.0f,
                0.5f, -0.5f, -0.5f,      1.0f,  0.0f,  0.0f,    1.0f, 1.0f,
                0.5f, -0.5f, -0.5f,      1.0f,  0.0f,  0.0f,    1.0f, 1.0f,
                0.5f, -0.5f,  0.5f,      1.0f,  0.0f,  0.0f,    0.0f, 1.0f,
                0.5f,  0.5f,  0.5f,      1.0f,  0.0f,  0.0f,    0.0f, 0.0f,
                                                                           
                -0.5f, -0.5f, -0.5f,     0.0f, -1.0f, 0.0f,     0.0f, 0.0f,
                0.5f, -0.5f, -0.5f,     0.0f, -1.0f, 0.0f,      1.0f, 0.0f,
                0.5f, -0.5f,  0.5f,     0.0f, -1.0f, 0.0f,      1.0f, 1.0f,
                0.5f, -0.5f,  0.5f,     0.0f, -1.0f, 0.0f,      1.0f, 1.0f,
                -0.5f, -0.5f,  0.5f,     0.0f, -1.0f, 0.0f,     0.0f, 1.0f,
                -0.5f, -0.5f, -0.5f,     0.0f, -1.0f, 0.0f,     0.0f, 0.0f,
                                                                           
                -0.5f,  0.5f, -0.5f,     0.0f,  1.0f, 0.0f,    0.0f, 0.0f, 
                0.5f,  0.5f, -0.5f,     0.0f,  1.0f, 0.0f,     1.0f, 0.0f, 
                0.5f,  0.5f,  0.5f,     0.0f,  1.0f, 0.0f,     1.0f, 1.0f, 
                0.5f,  0.5f,  0.5f,     0.0f,  1.0f, 0.0f,     1.0f, 1.0f, 
                -0.5f,  0.5f,  0.5f,     0.0f,  1.0f, 0.0f,    0.0f, 1.0f, 
                -0.5f,  0.5f, -0.5f,     0.0f,  1.0f, 0.0f,    0.0f, 0.0f
            };
            
            std::vector<unsigned int> indices;
            int sz = vertices.size() / sizeof(Vertex_P3_N3_T2) * sizeof(float);
            indices.resize(sz);
            for (int i = 0; i < indices.size(); i++)
            {
                indices[i] = i;
            }

            Mesh mesh = Mesh::createMesh<Vertex_P3_N3_T2>(vertices, indices);
            return Model({ mesh });
        }

        static Model sphere(float segmentsX, float segmentsY)
        {
            std::vector<Vertex_P3_N3_T2> vertices;
            vertices.reserve((segmentsX + 1) * (segmentsY + 1) * sizeof(Vertex_P3_N3_T2) / sizeof(float));
            for (unsigned int y = 0; y <= segmentsY; ++y)
            {
                for (unsigned int x = 0; x <= segmentsX; ++x)
                {
                    float xSegment = (float)x / (float)segmentsX;
                    float ySegment = (float)y / (float)segmentsY;
                    constexpr float PI = glm::pi<float>();
                    constexpr float TAU = glm::two_pi<float>();

                    float xPos = std::cos(xSegment * TAU) * std::sin(ySegment * PI);
                    float yPos = std::cos(ySegment * PI);
                    float zPos = std::sin(xSegment * TAU) * std::sin(ySegment * PI);

                    glm::vec3 pos { xPos, yPos, zPos };
                    glm::vec2 texCoord { xSegment, ySegment };

                    vertices.emplace_back(pos, -pos, texCoord);
                }
            }
            std::vector<unsigned int> indices;
            indices.reserve(segmentsX * segmentsY * 6);
            for (int y = 0; y < segmentsY; ++y)
            {
                for (int x = 0; x < segmentsX; ++x)
                {
                    indices.push_back((y + 1) * (segmentsX + 1) + x);
                    indices.push_back(y * (segmentsX + 1) + x);
                    indices.push_back(y * (segmentsX + 1) + x + 1);

                    indices.push_back((y + 1) * (segmentsX + 1) + x);
                    indices.push_back(y * (segmentsX + 1) + x + 1);
                    indices.push_back((y + 1) * (segmentsX + 1) + x + 1);
                }
            }

            Mesh mesh = Mesh::createMesh<Vertex_P3_N3_T2>(vertices, indices);
            std::shared_ptr<Texture> texture(Texture::create(512, 512, 0xffffffff));
            mesh.textures.push_back(texture);
            return Model({mesh});
        }
    };
}