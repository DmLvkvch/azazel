#pragma once

#include "../Layer.h"

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
    };
}