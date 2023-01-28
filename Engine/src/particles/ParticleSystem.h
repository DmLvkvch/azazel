#pragma once

#include <vector>
#include "ParticleEmitter.h"

namespace Azazel
{
    class ParticleSystem
    {
    private:
        std::vector<ParticleEmitter> emmiters;
    };
}