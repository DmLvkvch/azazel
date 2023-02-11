#pragma once

#include "Layer.h"

#include "camera/OrthographicCamera.h"
#include "render/Shader.h"
#include "render/Texture.h"
#include "render/VertexBuffer.h"
#include "render/IndexBuffer.h"
#include "render/VertexArray.h"
#include "render/FrameBuffer.h"

#include <memory>
#include <map>

namespace Azazel
{
    class TestLayer : public Layer
    {
       public:
        TestLayer() : Layer("Test Layer") {}
        ~TestLayer() {}

        void onAttach() override;
        void onDetach() override;
        void onInputUpdate(float delta) override;
        void onUpdate(float delta) override;
        void onEvent(Event& e) override;
 
    private:
        OrthographicCamera camera;
        std::unique_ptr<Shader> shader;
        std::unique_ptr<VertexArray> vertexArray;
        std::unique_ptr<IndexBuffer> indexBuffer;
        std::unique_ptr<Texture> texture;
    };
}