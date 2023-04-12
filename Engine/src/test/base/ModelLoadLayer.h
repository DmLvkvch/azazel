#pragma once

#include "Layer.h"
#include "camera/OrthographicCamera.h"
#include "camera/Camera.h"
#include "render/Model.h"
#include "render/renderers/SkyboxRenderer.h"
#include "render/MeshHelper.h"
#include "render/FrameBuffer.h"

namespace Azazel
{
    class ModelLoadLayer : public Layer
    {
    public:
        ModelLoadLayer();

        void onUpdate(float delta) override;
        void onRender(float delta) override;

        ~ModelLoadLayer();
    private:
        std::unique_ptr<Shader> light;
        
        std::unique_ptr<Shader> shadow;
        std::unique_ptr<Shader> shadowMap;
        std::unique_ptr<Shader> quadShader;

        std::unique_ptr<Texture> texture;

        Model model;
        Model floor;
        Model cube;
        
        Camera camera;
        SkyboxRenderer sbr;
        Mesh<Vertex_P3_T2> quad;

        std::unique_ptr<FrameBuffer> frameBuffer;

        std::unique_ptr<Texture> depthTexture;
        std::unique_ptr<Texture> texture1;

    };
}