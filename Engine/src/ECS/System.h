#pragma once

#include "Entity.h"
#include <set>

namespace Azazel
{
    class System
    {
    public:
        std::set<Entity> entities;
    };
}