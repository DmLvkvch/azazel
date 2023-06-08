#pragma once

#include "Application.h"
#include "ECS/System.h"

class Event;

namespace Azazel
{
    class CameraSystem : public System
    {
    public:
        void init()
        {

        }

	    void update(float dt);

    private:
	    void inputListener(Event& event);

    private:
	    std::bitset<8> mButtons;
    };
}