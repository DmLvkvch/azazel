#pragma once

#include "Layer.h"
#include <vector>
#include <string>

namespace Azazel
{
    class SkyBox : public Layer
    {
    public:
        SkyBox();
        ~SkyBox();
        unsigned int loadCubemap(std::vector<std::string> faces);
        void onAttach() override;
        void onDetach() override;
        void onUpdate() override;
        void onEvent(Event& e) override;
    };
}