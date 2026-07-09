#pragma once

#include "vortex/core/containers/vortex_array.hpp"

#include "vortex/ecs/entity_manager.hpp"
#include "vortex/ecs/component_pool.hpp"
#include "vortex/ecs/component_types.hpp"
#include "vortex/ecs/view.hpp"

#include "vortex/components/physics_components.hpp"
#include <memory>

namespace vortex::ecs
{
    constexpr size_t MAX_NUMBER_OF_COMPONENTS = 10;

    class Registry
    {
    public:
        Registry()
        {
            for (size_t i = 0; i < m_componentPools.capacity(); ++i)
            {
                m_componentPools.push_back(nullptr);
            }
        }

        template <typename... Comps>
        ComponentView<Comps...> getView()
        {
            return ComponentView<Comps...>(getPool<Comps>()...);
        }

        Entity createEntity()
        {
            return m_entityManager.create();
        }

        void destroyEntity(Entity ent)
        {
            for(size_t i = 0; i < MAX_NUMBER_OF_COMPONENTS; ++i)
            {
                if(m_componentPools[i])
                {
                    m_componentPools[i]->remove(ent);
                }
            }

            m_entityManager.destroy(ent);
        }

        template <typename T>
        void addComponent(Entity ent, const T &comp)
        {
            ensurePool<T>()->add(ent, comp);
        }

        template <typename T>
        void addComponent(Entity ent, T &&comp)
        {
            ensurePool<T>()->add(ent, std::move(comp));
        }

        template <typename T>
        void removeComponent(Entity ent)
        {
            ComponentPool<T> *pool_ptr = getPool<T>();
            if (pool_ptr)
                pool_ptr->remove(ent);
        }

        template <typename T>
        bool hasComponent(Entity ent) const
        {
            ComponentPool<T> *pool_ptr = getPool<T>();
            if (pool_ptr)
                return pool_ptr->has(ent);

            return false;
        }

        template <typename T>
        T &getComponent(Entity ent)
        {
            ComponentPool<T> *pool_ptr = getPool<T>();
            assert(pool_ptr && "No such pool in scope!");
            return pool_ptr->get(ent);
        }

        template <typename T>
        const T &getComponent(Entity ent) const
        {
            ComponentPool<T> *pool_ptr = getPool<T>();
            assert(pool_ptr && "No such pool in scope!");
            return pool_ptr->get(ent);
        }

    private:
        template <typename T>
        void registerComponent(ComponentTypeId type_id)
        {
            m_componentPools[type_id] = std::make_unique<ComponentPool<T>>();
        }

        template <typename T>
        ComponentPool<T> *ensurePool()
        {
            ComponentTypeId type_id = getComponentTypeId<T>();
            if (!m_componentPools[type_id])
                registerComponent<T>(type_id);

            ComponentPool<T> *pool_ptr = static_cast<ComponentPool<T> *>(m_componentPools[type_id].get());

            return pool_ptr;
        }

        template <typename T>
        ComponentPool<T> *getPool() const
        {
            ComponentTypeId type_id = getComponentTypeId<T>();

            ComponentPool<T> *pool_ptr = static_cast<ComponentPool<T> *>(m_componentPools[type_id].get());

            return pool_ptr;
        }

        EntityManager m_entityManager;
        core::VArray<std::unique_ptr<IPool>> m_componentPools{MAX_NUMBER_OF_COMPONENTS};
    };
}