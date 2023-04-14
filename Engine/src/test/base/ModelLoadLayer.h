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
        
        Shader* shadow;
        Shader* shadowMap;
        Shader* quadShader;

        Texture* texture;

        FrameBuffer* frameBuffer;

        Texture* depthTexture;

        Model model;
        Model floor;
        Model cube;
        
        Camera camera;
        SkyboxRenderer sbr;
        Mesh<Vertex_P3_T2> quad;
    };
}