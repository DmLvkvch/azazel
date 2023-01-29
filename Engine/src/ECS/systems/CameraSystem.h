#pragma once

#include "ECS/System.h"

class Event;

namespace Azazel
{
    class CameraSystem
    {
    public:
        void init();
	    void update(float dt);

    private:
	    void inputListener(Event& event);

    private:
	    std::bitset<8> mButtons;
    };
}