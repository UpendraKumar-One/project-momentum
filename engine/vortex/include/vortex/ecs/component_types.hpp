#pragma once

#include <cstddef>

namespace Vortex::Ecs
{
    using ComponentTypeID = size_t;

    inline ComponentTypeID GetUniqueID()
    {
        static ComponentTypeID lastID = 0;
        return lastID++;
    }

    template <typename T>
    inline ComponentTypeID GetComponentTypeID()
    {
        static const ComponentTypeID typeID = GetUniqueID();
        return typeID;
    }
}