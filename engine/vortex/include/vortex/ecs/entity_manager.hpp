#pragma once

#include "vortex/ecs/entity.hpp"
#include <bitset>

namespace vortex::ecs
{
    class EntityManager
    {
    public:

        EntityManager();
        ~EntityManager();

        Entity create();
        void destroy(Entity ent);
        bool isActive(Entity ent);

    private:
        int m_entitiesLeft;
        uint16_t m_activeEntities;
        uint16_t m_nextFreeEntity;
        uint16_t* m_entities;
        std::bitset<0x1000> m_isActiveFlags;
    };
}