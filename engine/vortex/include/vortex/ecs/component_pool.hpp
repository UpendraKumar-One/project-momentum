#pragma once

#include "vortex/core/containers/vortex_array.hpp"
#include "vortex/ecs/entity_manager.hpp"
#include <utility>
#include <cassert>

namespace Vortex::Ecs
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

        virtual void Remove(entity ent) = 0;

        virtual const Core::VArray<uint16_t>& GetEntityList() const = 0;
    };

    template <typename T>
    class ComponentPool : public IPool
    {
    public:
        ComponentPool()
        {
            for (size_t i = 0; i < MAX_ENTITIES; ++i)
            {
                v_sparseArray_.push_back(ComponentPoolConstants::NULL_INDEX);
            }
        }

        void Add(entity ent, const T &component)
        {
            uint16_t index = GetEntityIndex(ent);
            if (v_sparseArray_[index] == ComponentPoolConstants::NULL_INDEX)
            {
                v_sparseArray_[index] = v_denseArray_.size();
                v_denseArray_.push_back(component);
                v_denseToSparse_.push_back(index);
                return;
            }

            v_denseArray_[v_sparseArray_[index]] = component;
        }

        void Add(entity ent, T &&component)
        {
            uint16_t index = GetEntityIndex(ent);
            if (v_sparseArray_[index] == ComponentPoolConstants::NULL_INDEX)
            {
                v_sparseArray_[index] = v_denseArray_.size();
                v_denseArray_.push_back(std::move(component));
                v_denseToSparse_.push_back(index);
                return;
            }

            v_denseArray_[v_sparseArray_[index]] = std::move(component);
        }

        inline bool Has(entity ent)
        {
            return v_sparseArray_[GetEntityIndex(ent)] != ComponentPoolConstants::NULL_INDEX;
        }

        T &Get(entity ent)
        {
            assert(Has(ent) && "Provided entity doesn't have the component!");

            return v_denseArray_[v_sparseArray_[GetEntityIndex(ent)]];
        }

        const T &Get(entity ent) const
        {
            assert(Has(ent) && "Provided entity doesn't have the component!");

            return v_denseArray_[v_sparseArray_[GetEntityIndex(ent)]];
        }

        void Remove(entity ent) override
        {
            if (!Has(ent))
                return;

            uint16_t removed_index = GetEntityIndex(ent);
            uint16_t last_index = v_denseToSparse_.back();

            if (v_sparseArray_[removed_index] != v_sparseArray_[last_index])
            {
                v_denseArray_[v_sparseArray_[removed_index]] = std::move(v_denseArray_.back());
                v_denseToSparse_[v_sparseArray_[removed_index]] = last_index;
                v_sparseArray_[last_index] = v_sparseArray_[removed_index];
            }

            v_sparseArray_[removed_index] = ComponentPoolConstants::NULL_INDEX;

            v_denseArray_.pop_back();
            v_denseToSparse_.pop_back();
        }

        ComponentPool<T>* CastToType(void* ptr)
        {
            return static_cast<ComponentPool<T>*>(ptr);
        }

        size_t size() const override
        {
            return v_denseArray_.size();
        }

        const Core::VArray<uint16_t>& GetEntityList() const override
        {
            return v_denseToSparse_;
        }

    private:
        Core::VArray<uint16_t> v_sparseArray_{MAX_ENTITIES};
        Core::VArray<uint16_t> v_denseToSparse_{MAX_ENTITIES};
        Core::VArray<T> v_denseArray_{MAX_ENTITIES};
    };
}