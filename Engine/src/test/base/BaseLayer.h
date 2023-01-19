#pragma once

#include <Layer.h>

#include <renderer/OrthographicCamera.h>
#include <renderer/Shader.h>
#include <renderer/Texture.h>
#include <renderer/VertexBuffer.h>
#include <renderer/IndexBuffer.h>
#include <renderer/VertexArray.h>
#include <renderer/FrameBuffer.h>
#include <memory>
#include <Transform.h>
#include <renderer/Mesh.h>

namespace Azazel
{
    class BaseLayer : public Layer
    {
    public:
        BaseLayer() : Layer("Base Layer") {}
        ~BaseLayer() {}

        void onAttach() override;
        void onDetach() override;
        void onUpdate(float delta) override;
        void onEvent(Event& e) override;
        void onImguiRender(float delta) override;
    private:
        void drawImgui();
        void updateBlendEquation();
    private:
        OrthographicCamera camera;
        std::unique_ptr<Texture> texture;
        std::unique_ptr<Texture> texture1;
        std::unique_ptr<Shader> shader;
        std::unique_ptr<IndexBuffer> indexBuffer;
        std::unique_ptr<VertexArray> vertexArray;
        Transform transform;
        glm::vec4 color;
        Mesh<Vertex_P3_T2> mesh;
    };
}