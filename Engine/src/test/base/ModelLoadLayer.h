#pragma once

#include "Layer.h"
#include "camera/OrthographicCamera.h"
#include "camera/Camera.h"
#include "render/Model.h"
#include "render/renderers/SkyboxRenderer.h"

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
        Model model;
        Camera camera;
        SkyboxRenderer sbr;
    };
}