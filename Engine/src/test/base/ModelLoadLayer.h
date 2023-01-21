#pragma once

#include <Layer.h>
#include <renderer/Model.h>
#include <renderer/Mesh.h>
#include <renderer/Vertex.h>

namespace Azazel
{
    class ModelLoadLayer : public Layer
    {
    public:
        ModelLoadLayer() : Layer("Model Load Example")
        {
        }

        ~ModelLoadLayer() {}
    private:
        Model model;
    };
}