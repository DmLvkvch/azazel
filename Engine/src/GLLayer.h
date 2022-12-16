#pragma once

#include "Layer.h"

#include "renderer/Camera.h"

#include "renderer/Shader.h"
#include "renderer/Texture.h"
#include "renderer/VertexBuffer.h"
#include "renderer/IndexBuffer.h"
#include "renderer/VertexArray.h"

#include <memory>

namespace Azazel
{
    class GLLayer : public Layer
    {
    public:
        Camera camera;

        GLLayer()
        : Layer("ImGuiLayer")
        {
            
        }
        ~GLLayer()
        {

        }

        void onAttach() override;
        void onDetach() override;
        void onUpdate() override;
        void onEvent(Event& e) override;
 
    private:
        std::unique_ptr<Shader> shader;
        std::unique_ptr<VertexArray> vertexArray;
        std::unique_ptr<VertexBuffer> vertexBuffer;
        std::unique_ptr<IndexBuffer> indexBuffer;
        std::unique_ptr<Texture> texture;
        std::unique_ptr<Texture> face;
    };
}