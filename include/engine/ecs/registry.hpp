#pragma once

#include "engine/core/lazy_array.hpp"

#include "engine/ecs/entity_manager.hpp"
#include "engine/ecs/component_pool.hpp"
#include "engine/ecs/component_types.hpp"
#include "engine/ecs/view.hpp"

#include "engine/components/physics_components.hpp"

constexpr size_t MAX_NUMBER_OF_COMPONENTS = 10;

class Registry
{
public:
    Registry()
    {
        for (size_t i = 0; i < v_componentPools_.capacity(); ++i)
        {
            v_componentPools_.push_back(nullptr);
        }
    }

    template <typename... Components>
    ComponentView<Components...> GetView()
    {
        return ComponentView<Components...>(GetPool<Components>()...);
    }

    entity CreateEntity()
    {
        return ent_manager_.Create();
    }

    void DestroyEntity(entity ent)
    {
        for(size_t i = 0; i < MAX_NUMBER_OF_COMPONENTS; ++i)
        {
            if(v_componentPools_[i])
            {
                v_componentPools_[i]->Remove(ent);
            }
        }

        ent_manager_.Destroy(ent);
    }

    template <typename T>
    void AddComponent(entity ent, const T &comp)
    {
        EnsurePool<T>()->Add(ent, comp);
    }

    template <typename T>
    void AddComponent(entity ent, T &&comp)
    {
        EnsurePool<T>()->Add(ent, std::move(comp));
    }

    template <typename T>
    void RemoveComponent(entity ent)
    {
        ComponentPool<T> *pool_ptr = GetPool<T>();
        if (pool_ptr)
            pool_ptr->Remove(ent);
    }

    template <typename T>
    bool HasComponent(entity ent) const
    {
        ComponentPool<T> *pool_ptr = GetPool<T>();
        if (pool_ptr)
            return pool_ptr->Has(ent);

        return false;
    }

    template <typename T>
    T &GetComponent(entity ent)
    {
        ComponentPool<T> *pool_ptr = GetPool<T>();
        assert(pool_ptr && "No such pool in scope!");
        return pool_ptr->Get(ent);
    }

    template <typename T>
    const T &GetComponent(entity ent) const
    {
        ComponentPool<T> *pool_ptr = GetPool<T>();
        assert(pool_ptr && "No such pool in scope!");
        return pool_ptr->Get(ent);
    }

private:
    template <typename T>
    void RegisterComponent(ComponentTypeID typeID)
    {
        v_componentPools_[typeID] = std::make_unique<ComponentPool<T>>();
    }

    template <typename T>
    ComponentPool<T> *EnsurePool()
    {
        ComponentTypeID typeID = GetComponentTypeID<T>();
        if (!v_componentPools_[typeID])
            RegisterComponent<T>(typeID);

        ComponentPool<T> *pool_ptr = static_cast<ComponentPool<T> *>(v_componentPools_[typeID].get());

        return pool_ptr;
    }

    template <typename T>
    ComponentPool<T> *GetPool() const
    {
        ComponentTypeID typeID = GetComponentTypeID<T>();

        ComponentPool<T> *pool_ptr = static_cast<ComponentPool<T> *>(v_componentPools_[typeID].get());

        return pool_ptr;
    }

    EntityManager ent_manager_;
    LazyArray<std::unique_ptr<IPool>> v_componentPools_{MAX_NUMBER_OF_COMPONENTS};
};