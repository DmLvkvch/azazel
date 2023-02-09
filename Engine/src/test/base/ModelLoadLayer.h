#pragma once

#include "Layer.h"
#include "renderer/Model.h"
#include "camera/OrthographicCamera.h"
#include "camera/Camera.h"

namespace Azazel
{
    class ModelLoadLayer : public Layer
    {
    public:
        ModelLoadLayer();

        void onUpdate(float delta) override;
        void onRender(float delta) override;

        ~ModelLoadLayer() {}
    private:
        std::unique_ptr<Shader> light;
        std::unique_ptr<Texture> texture;
        Model model;
        Camera camera;
    };
}