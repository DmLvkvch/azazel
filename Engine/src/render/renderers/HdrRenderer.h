#pragma once

#include "render/Render.h"
#include "render/FrameBuffer.h"
#include "render/MeshHelper.h"
#include <memory>
#include "api/file/FileUtils.h"
#include "resources/ResourceManager.h"

namespace Azazel
{
    class HdrRenderer
    {
    public:
        HdrRenderer()
        {
            colorTexture = Texture::create(TextureData(1024, 1024, 8, nullptr));
            depthTexture = Texture::createDepthTexture(1024, 1024);
            frameBuffer = FrameBuffer::create(colorTexture, depthTexture);
            quad = MeshHelper::genQuadMesh();
            shader = ResourceManagers::shaderResourceManager->loadResource("shaders/default.vert.glsl", "shaders/hdr.frag.glsl", false);
            shader->bind();
            shader->setBool("hdr", true);
            shader->setMatrix4f("u_mvp", glm::mat4(1.0f));
            shader->setFloat("exposure", exp);
            shader->setTexture("u_texture_0", *colorTexture, 0);
        }

        ~HdrRenderer()
        {
            delete frameBuffer;
            delete colorTexture;
            delete depthTexture;
            delete shader;
        }

        void bind()
        {
            frameBuffer->bind();
        }

        void unbind()
        {
            frameBuffer->unbind();
        }

        void draw()
        {
            auto renderer = Render::getRender();
            colorTexture->bind(0);
            renderer->drawMesh<Vertex_P3_T2>(quad, *shader);
        }

        FrameBuffer* frameBuffer;
        Texture* colorTexture;
        Texture* depthTexture;
        Shader* shader;
        Mesh<Vertex_P3_T2> quad;
        float exp = 1.0f;
    };
}