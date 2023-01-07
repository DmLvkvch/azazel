#pragma once

#include "Layer.h"

#include "renderer/OrthographicCamera.h"
#include "renderer/Shader.h"
#include "renderer/Texture.h"
#include "renderer/VertexBuffer.h"
#include "renderer/IndexBuffer.h"
#include "renderer/VertexArray.h"
#include "renderer/FrameBuffer.h"
#include <memory>

namespace Azazel
{
    class TestLayer : public Layer
    {
       public:
        TestLayer()
        : Layer("Test Layer")
        {
            
        }
        ~TestLayer()
        {

        }

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