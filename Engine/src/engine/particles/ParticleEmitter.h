#pragma once

#include <vector>

#include "Particle.h"

namespace Azazel
{
    class ParticleEmitter
    {
        std::vector<Particle> particles;

        ParticleEmitter()
        {
            particles.resize(1000);
        }

        void update(float delta)
        {
            for (auto& particle : particles)
            {
                if (!particle.active)
                {
                    continue;
                }
                if (particle.lifeRemaining <= 0.0f)
                {
                    particle.active = false;
                    continue;
                }
                particle.position += particle.velocity * delta;
		        particle.rotation += 0.01f * delta;
            }
        }

        void emit(int count)
        {

        }
    };
}