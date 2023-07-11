#pragma once

#include "Layer.h"
#include "camera/OrthographicCamera.h"
#include "camera/Camera.h"
#include "render/Model.h"
#include "render/renderers/SkyboxRenderer.h"
#include "render/renderers/HdrRenderer.h"
#include "render/MeshHelper.h"
#include "render/FrameBuffer.h"

#include "render/Material.h"

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
        
        Shader* shadow;
        Shader* shadowMap;

        FrameBuffer* frameBuffer;

        Texture* depthTexture;

        Model model;
        Model floor;
        Model cube;
        Model sphere;

        Model cerberus;
        Material material;
        SkyboxRenderer sbr;
        HdrRenderer hdrRenderer;
        Mesh quad;
    };
}