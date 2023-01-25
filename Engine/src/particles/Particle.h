#pragma once

namespace Azazel
{
    class Particle
    {
    public:
        glm::vec3 position;
		glm::vec2 velocity;
		glm::vec4 colorBegin;
        glm::vec4 colorEnd;
		float rotation = 0.0f;
		float sizeBegin;
        float sizeEnd;

		float lifeTime = 1.0f;
		float lifeRemaining = 0.0f;

		bool active = false;
    };
}