#pragma once

#include "Layer.h"

#include "Camera.h"

#include "renderer/rhi/ShaderRHI.h"
#include "renderer/rhi/TextureRHI.h"
#include "renderer/rhi/VertexBufferRHI.h"
#include "renderer/rhi/IndexBufferRHI.h"
#include "renderer/rhi/VertexArrayRHI.h"

namespace Azazel
{
    class GLLayer : public Layer
    {
    public:
        Camera camera;
        TextureRHI* texture;
        VertexArrayRHI* vertexArray;
        IndexBufferRHI* indexBuffer;
        VertexBufferRHI* vertexBuffer;
        ShaderRHI* shader;

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