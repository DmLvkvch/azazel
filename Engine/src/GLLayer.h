#pragma once

#include "Layer.h"

#include "Camera.h"

#include "renderer/Shader.h"
#include "renderer/Texture.h"
#include "renderer/VertexBuffer.h"
#include "renderer/IndexBuffer.h"
#include "renderer/VertexArray.h"

namespace Azazel
{
    class GLLayer : public Layer
    {
    public:
        Camera camera;
        Texture* texture;
        VertexArray* vertexArray;
        IndexBuffer* indexBuffer;
        VertexBuffer* vertexBuffer;
        Shader* shader;

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
    };
}