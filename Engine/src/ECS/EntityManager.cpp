#include "EntityManager.h"

#include <cassert>

namespace Azazel
{
    Entity EntityManager::id = 1;

    EntityManager::EntityManager()
    {
      for (Entity entity = 0; entity < MAX_ENTITIES; ++entity)
      {
        availableEntities.push(entity);
      }
    }

    Entity EntityManager::createEntity()
    {
        assert(EntityManager::id < MAX_ENTITIES && "Too many entities in existence.");
        Entity id = availableEntities.front();
        availableEntities.pop();
        ++EntityManager::id;
        return id;
    }

    void EntityManager::destroyEntity(Entity entity)
    {
        assert(entity < MAX_ENTITIES && "Entity out of range.");
        signatures[entity].reset();
        availableEntities.push(entity);
        --EntityManager::id;
    }

    void EntityManager::setSignature(Entity entity, Signature signature)
    {
        assert(entity < MAX_ENTITIES && "Entity out of range.");
        signatures[entity] = signature;
    }

    Signature EntityManager::getSignature(Entity entity)
    {
      assert(entity < MAX_ENTITIES && "Entity out of range.");
      return signatures[entity];
    }
}