#pragma once

#include <Layer.h>
#include <renderer/Model.h>
#include <renderer/Mesh.h>
#include <renderer/Vertex.h>
#include <FileUtils.h>
#include <TextureUtils.h>

namespace Azazel
{
    class ModelLoadLayer : public Layer
    {
    public:
        ModelLoadLayer();

        void onUpdate(float delta) override;

        ~ModelLoadLayer() {}
    private:
        std::unique_ptr<Shader> shader;
        std::unique_ptr<Shader> light;
        std::unique_ptr<Texture> texture;
        Model model;
    };
}