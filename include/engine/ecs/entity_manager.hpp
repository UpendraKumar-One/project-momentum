#pragma once

#include "entity.hpp"
#include <bitset>

class EntityManager
{
public:

    EntityManager();
    ~EntityManager();

    entity Create();
    void Destroy(entity);
    bool IsActive(entity);

private:
    int i_entitiesLeft_;
    uint16_t i_activeEntities_;
    uint16_t i_nextFreeEntity_;
    uint16_t* v_entities_;
    std::bitset<0x1000> b_isActiveFlags_;
};