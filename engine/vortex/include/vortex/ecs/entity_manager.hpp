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
        VxEntity m_activeEntities;
        VxEntity m_nextFreeEntity;
        VxEntity* m_entities;
        std::bitset<0x1000> m_isActiveFlags;
    };
}