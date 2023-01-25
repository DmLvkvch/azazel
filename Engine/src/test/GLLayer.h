#pragma once

#include "Layer.h"

#include "renderer/Camera.h"
#include "renderer/OrthographicCamera.h"

#include "renderer/Shader.h"
#include "renderer/Texture.h"
#include "renderer/VertexBuffer.h"
#include "renderer/IndexBuffer.h"
#include "renderer/VertexArray.h"
#include "renderer/FrameBuffer.h"
#include <memory>
#include "renderer/Model.h"

namespace Azazel
{
    class GLLayer : public Layer
    {
    public:
        Camera camera;
        OrthographicCamera orthographicCamera;

        GLLayer() : Layer("GL Layer")
        {
        }

        ~GLLayer()
        {
        }

        void onAttach() override;
        void onDetach() override;
        void onUpdate(float delta) override;
        void onEvent(Event& e) override;
 
    private:
        glm::vec2 r { 0.1f, 0.1f };
        
        Model model;
        
        Mesh<Vertex_P3_T2> gridMesh;
        
        std::unique_ptr<Texture> face;

        std::unique_ptr<Shader> shader;
        std::unique_ptr<Shader> testShader;
    };
}