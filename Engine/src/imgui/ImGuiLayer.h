#pragma once

#include "Layer.h"

namespace Azazel
{
    class ImGuiLayer : public Layer
    {
    public:
        ImGuiLayer();
        ~ImGuiLayer();
        void onAttach() override;
        void onDetach() override;
        void onUpdate(float delta) override;
        void onEvent(Event& e) override;
        void onInputUpdate(float delta) override;
    private:
        int n = 0;
        float dt = 0.0f;
        float fps = 144.0f;
    };
}