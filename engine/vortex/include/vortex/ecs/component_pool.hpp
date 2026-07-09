#pragma once

#include "vortex/core/containers/vortex_array.hpp"
#include "vortex/ecs/entity_manager.hpp"
#include <utility>
#include <cassert>

namespace vortex::ecs
{
    namespace ComponentPoolConstants
    {
        constexpr uint16_t NULL_INDEX = 0xFFFF;
    }

    class IPool
    {
    public:
        virtual ~IPool() = default;

        virtual size_t size() const = 0;

        virtual void remove(Entity ent) = 0;

        virtual const vortex::core::VArray<uint16_t>& getEntityList() const = 0;
    };

    template <typename T>
    class ComponentPool : public IPool
    {
    public:
        ComponentPool()
        {
            for (size_t i = 0; i < MAX_ENTITIES; ++i)
            {
                m_sparseArray.push_back(ComponentPoolConstants::NULL_INDEX);
            }
        }

        void add(Entity ent, const T &component)
        {
            uint16_t index = getEntityIndex(ent);
            if (m_sparseArray[index] == ComponentPoolConstants::NULL_INDEX)
            {
                m_sparseArray[index] = m_denseArray.size();
                m_denseArray.push_back(component);
                m_denseToSparse.push_back(index);
                return;
            }

            m_denseArray[m_sparseArray[index]] = component;
        }

        void add(Entity ent, T &&component)
        {
            uint16_t index = getEntityIndex(ent);
            if (m_sparseArray[index] == ComponentPoolConstants::NULL_INDEX)
            {
                m_sparseArray[index] = m_denseArray.size();
                m_denseArray.push_back(std::move(component));
                m_denseToSparse.push_back(index);
                return;
            }

            m_denseArray[m_sparseArray[index]] = std::move(component);
        }

        inline bool has(Entity ent)
        {
            return m_sparseArray[getEntityIndex(ent)] != ComponentPoolConstants::NULL_INDEX;
        }

        T &get(Entity ent)
        {
            assert(has(ent) && "Provided entity doesn't have the component!");

            return m_denseArray[m_sparseArray[getEntityIndex(ent)]];
        }

        const T &get(Entity ent) const
        {
            assert(has(ent) && "Provided entity doesn't have the component!");

            return m_denseArray[m_sparseArray[getEntityIndex(ent)]];
        }

        void remove(Entity ent) override
        {
            if (!has(ent))
                return;

            uint16_t removed_index = getEntityIndex(ent);
            uint16_t last_index = m_denseToSparse.back();

            if (m_sparseArray[removed_index] != m_sparseArray[last_index])
            {
                m_denseArray[m_sparseArray[removed_index]] = std::move(m_denseArray.back());
                m_denseToSparse[m_sparseArray[removed_index]] = last_index;
                m_sparseArray[last_index] = m_sparseArray[removed_index];
            }

            m_sparseArray[removed_index] = ComponentPoolConstants::NULL_INDEX;

            m_denseArray.pop_back();
            m_denseToSparse.pop_back();
        }

        ComponentPool<T>* castToType(void* ptr)
        {
            return static_cast<ComponentPool<T>*>(ptr);
        }

        size_t size() const override
        {
            return m_denseArray.size();
        }

        const core::VArray<uint16_t>& getEntityList() const override
        {
            return m_denseToSparse;
        }

    private:
        core::VArray<uint16_t> m_sparseArray{MAX_ENTITIES};
        core::VArray<uint16_t> m_denseToSparse{MAX_ENTITIES};
        core::VArray<T> m_denseArray{MAX_ENTITIES};
    };
}