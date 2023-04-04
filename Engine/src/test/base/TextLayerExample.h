#pragma once

#include "Layer.h"
#include "camera/OrthographicCamera.h"

namespace Azazel
{       
    class TextLayerExample : public Layer
    {
    public:
        TextLayerExample() : Layer("Text Layer") {}
        ~TextLayerExample() {}

        void onAttach() override;
        void onDetach() override;
        void onInputUpdate(float delta) override;
        void onUpdate(float delta) override;
        void onRender(float delta) override;
        void onEvent(Event& e) override;
 
    private:
        OrthographicCamera camera;
    };
}