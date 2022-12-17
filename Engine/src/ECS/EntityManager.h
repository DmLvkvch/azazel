#pragma once

#include "Entity.h"

#include <queue>
#include <array>

namespace Azazel
{
    class EntityManager
    {
    public:
        EntityManager();

        Entity createEntity();

        void destroyEntity(Entity entity);

        void setSignature(Entity entity, Signature signature);

        Signature getSignature(Entity entity);

    private:
        // Queue of unused entity IDs
        std::queue<Entity> availableEntities;

        // Array of signatures where the index corresponds to the entity ID
        std::array<Signature, MAX_ENTITIES> signatures{};

        static Entity id;
    };
}