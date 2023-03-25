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
        void update(float f);

        ~ModelLoadLayer();
    private:
        std::unique_ptr<Shader> light;
        std::unique_ptr<Texture> texture;
        std::unique_ptr<Texture> textureTest;
        Model model;
        Camera camera;
        SkyboxRenderer sbr;
        Mesh<Vertex_P3_T2> quad;
        std::unique_ptr<FrameBuffer> fb;
        std::unique_ptr<Texture> depthTexture;
        std::unique_ptr<Shader> s;
    };
}