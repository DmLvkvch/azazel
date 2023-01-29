#pragma once

#include "ECS/System.h"

namespace Azazel
{
    class PhysicsSystem : public System
    {
    public:
        void init();

        void update(float dt);
    };
}