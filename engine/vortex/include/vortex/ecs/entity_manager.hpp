#pragma once

#include "vortex/ecs/entity.hpp"
#include <bitset>

namespace vortex::ecs
{
    class VxEntityManager
    {
    public:

        VxEntityManager();
        ~VxEntityManager();

        VxEntity create();
        void destroy(VxEntity ent);
        bool isActive(VxEntity ent);

    private:
        int m_entitiesLeft;
        uint16_t m_activeEntities;
        uint16_t m_nextFreeEntity;
        uint16_t* m_entities;
        std::bitset<0x1000> m_isActiveFlags;
    };
}