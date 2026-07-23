#pragma once

#include "vortex/core/containers/vortex_array.hpp"
#include "vortex/ecs/entity_manager.hpp"
#include "vortex/core/config/vortex_config.hpp"
#include <utility>
#include <cassert>

namespace vortex::ecs
{
    class IPool
    {
    public:
        virtual ~IPool() = default;

        virtual size_t size() const = 0;

        virtual void remove(VxEntity ent) = 0;

        virtual const vortex::containers::VxArray<VxEntity>& getEntityList() const = 0;
    };

    template <typename T>
    class VxComponentPool : public IPool
    {
    public:
        VxComponentPool()
        {
            for (size_t i = 0; i < config::MAX_ENTITIES; ++i)
            {
                m_sparseArray.push_back(config::NULL_ENTITY);
            }
        }

        void add(VxEntity ent, const T &component)
        {
            VxEntity index = getEntityIndex(ent);
            if (m_sparseArray[index] == config::NULL_ENTITY)
            {
                m_sparseArray[index] = static_cast<VxEntity>(m_denseArray.size());
                m_denseArray.push_back(component);
                m_denseToSparse.push_back(index);
                return;
            }

            m_denseArray[m_sparseArray[index]] = component;
        }

        void add(VxEntity ent, T &&component)
        {
            VxEntity index = getEntityIndex(ent);
            if (m_sparseArray[index] == config::NULL_ENTITY)
            {
                m_sparseArray[index] = static_cast<VxEntity>(m_denseArray.size());
                m_denseArray.push_back(std::move(component));
                m_denseToSparse.push_back(index);
                return;
            }

            m_denseArray[m_sparseArray[index]] = std::move(component);
        }

        inline bool has(VxEntity ent)
        {
            return m_sparseArray[getEntityIndex(ent)] != config::NULL_ENTITY;
        }

        T &get(VxEntity ent)
        {
            assert(has(ent) && "Provided entity doesn't have the component!");

            return m_denseArray[m_sparseArray[getEntityIndex(ent)]];
        }

        const T &get(VxEntity ent) const
        {
            assert(has(ent) && "Provided entity doesn't have the component!");

            return m_denseArray[m_sparseArray[getEntityIndex(ent)]];
        }

        void remove(VxEntity ent) override
        {
            if (!has(ent))
                return;

            VxEntity removed_index = getEntityIndex(ent);
            VxEntity last_index = m_denseToSparse.back();

            if (m_sparseArray[removed_index] != m_sparseArray[last_index])
            {
                m_denseArray[m_sparseArray[removed_index]] = std::move(m_denseArray.back());
                m_denseToSparse[m_sparseArray[removed_index]] = last_index;
                m_sparseArray[last_index] = m_sparseArray[removed_index];
            }

            m_sparseArray[removed_index] = config::NULL_ENTITY;

            m_denseArray.pop_back();
            m_denseToSparse.pop_back();
        }

        VxComponentPool<T>* castToType(void* ptr)
        {
            return static_cast<VxComponentPool<T>*>(ptr);
        }

        size_t size() const override
        {
            return m_denseArray.size();
        }

        const containers::VxArray<VxEntity>& getEntityList() const override
        {
            return m_denseToSparse;
        }

    private:
        containers::VxArray<VxEntity> m_sparseArray{config::MAX_ENTITIES};
        containers::VxArray<VxEntity> m_denseToSparse{config::MAX_ENTITIES};
        containers::VxArray<T> m_denseArray{config::MAX_ENTITIES};
    };
}