#pragma once

#include "Layer.h"
#include "camera/OrthographicCamera.h"
#include "render/Shader.h"
#include "render/Texture.h"
#include "render/VertexBuffer.h"
#include "render/IndexBuffer.h"
#include "render/VertexArray.h"
#include "render/Transform.h"
#include "render/Mesh.h"

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
        void onRender(float delta) override;
        void onEvent(Event& e) override;
        void onImguiRender(float delta) override;
    private:
        void drawImgui(float delta);
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
        Mesh<Vertex_P3_C4_T2> mesh;
    };
}