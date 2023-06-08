#pragma once

#include "Layer.h"

#include "camera/Camera.h"
#include "camera/OrthographicCamera.h"

#include "render/Shader.h"
#include "render/Texture.h"
#include "render/VertexBuffer.h"
#include "render/IndexBuffer.h"
#include "render/VertexArray.h"
#include "render/FrameBuffer.h"
#include "render/Model.h"

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
        
        Mesh gridMesh;
        
        std::unique_ptr<Texture> face;

        std::unique_ptr<Shader> shader;
        std::unique_ptr<Shader> testShader;
    };
}