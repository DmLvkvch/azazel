#pragma once

#include "Entity.h"
#include <unordered_map>
#include <array>

namespace Azazel
{
    class IComponentArray
    {
    public:
        virtual ~IComponentArray() = default;
        virtual void entityDestroyed(Entity entity) = 0;
    };


    template<typename T>
    class ComponentArray : public IComponentArray
    {
    public:
        void insertData(Entity entity, T component)
        {
		    assert(entityToIndexMap.find(entity) == mEntityToIndexMap.end() && "Component added to same entity more than once.");
            // Put new entry at end and update the maps
            size_t newIndex = mSize;
            entityToIndexMap[entity] = newIndex;
            indexToEntityMap[newIndex] = entity;
            componentArray[newIndex] = component;
            ++size;
        }

        void removeData(Entity entity)
        {
    		assert(mEntityToIndexMap.find(entity) != entityToIndexMap.end() && "Removing non-existent component.");
            // Copy element at end into deleted element's place to maintain density
            size_t indexOfRemovedEntity = entityToIndexMap[entity];
            size_t indexOfLastElement = mSize - 1;
            componentArray[indexOfRemovedEntity] = componentArray[indexOfLastElement];

            // Update map to point to moved spot
            Entity entityOfLastElement = mIndexToEntityMap[indexOfLastElement];
            entityToIndexMap[entityOfLastElement] = indexOfRemovedEntity;
            indexToEntityMap[indexOfRemovedEntity] = entityOfLastElement;

            entityToIndexMap.erase(entity);
            indexToEntityMap.erase(indexOfLastElement);

            --mSize;
        }

        T& getData(Entity entity)
        {
            assert(entityToIndexMap.find(entity) != entityToIndexMap.end() && "Retrieving non-existent component.");
            // Return a reference to the entity's component
            return componentArray[entityToIndexMap[entity]];
        }

        void entityDestroyed(Entity entity) override
        {
            if (entityToIndexMap.find(entity) != entityToIndexMap.end())
            {
                // Remove the entity's component if it existed
                RemoveData(entity);
            }
        }

    private:
        // The packed array of components (of generic type T),
        // set to a specified maximum amount, matching the maximum number
        // of entities allowed to exist simultaneously, so that each entity
        // has a unique spot.
        std::array<T, MAX_ENTITIES> componentArray;

        // Map from an entity ID to an array index.
        std::unordered_map<Entity, size_t> entityToIndexMap;

        // Map from an array index to an entity ID.
        std::unordered_map<size_t, Entity> indexToEntityMap;

        // Total size of valid entries in the array.
        size_t size;
    };
}