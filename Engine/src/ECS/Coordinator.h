#pragma once

#include "ComponentManager.h"
#include "EntityManager.h"
#include "SystemManager.h"
#include <memory>

namespace Azazel
{
    class Coordinator
    {
    public:
        void init()
        {
            // Create pointers to each manager
            componentManager = std::make_unique<ComponentManager>();
            entityManager = std::make_unique<EntityManager>();
            systemManager = std::make_unique<SystemManager>();
        }


        // Entity methods
        Entity createEntity()
        {
            return entityManager->createEntity();
        }

        void destroyEntity(Entity entity)
        {
            entityManager->destroyEntity(entity);

            componentManager->entityDestroyed(entity);

            systemManager->entityDestroyed(entity);
        }


        // Component methods
        template<typename T>
        void registerComponent()
        {
            componentManager->RegisterComponent<T>();
        }

        template<typename T>
        void addComponent(Entity entity, T component)
        {
            componentManager->AddComponent<T>(entity, component);

            auto signature = entityManager->GetSignature(entity);
            signature.set(componentManager->GetComponentType<T>(), true);
            entityManager->SetSignature(entity, signature);

            systemManager->EntitySignatureChanged(entity, signature);
        }

        template<typename T>
        void removeComponent(Entity entity)
        {
            componentManager->RemoveComponent<T>(entity);

            auto signature = entityManager->GetSignature(entity);
            signature.set(componentManager->GetComponentType<T>(), false);
            entityManager->SetSignature(entity, signature);

            systemManager->EntitySignatureChanged(entity, signature);
        }

        template<typename T>
        T& getComponent(Entity entity)
        {
            return componentManager->GetComponent<T>(entity);
        }

        template<typename T>
        ComponentType getComponentType()
        {
            return componentManager->GetComponentType<T>();
        }


        // System methods
        template<typename T>
        std::shared_ptr<T> registerSystem()
        {
            return systemManager->RegisterSystem<T>();
        }

        template<typename T>
        void setSystemSignature(Signature signature)
        {
            systemManager->SetSignature<T>(signature);
        }

    private:
        std::unique_ptr<ComponentManager> componentManager;
        std::unique_ptr<EntityManager> entityManager;
        std::unique_ptr<SystemManager> systemManager;
    };
}