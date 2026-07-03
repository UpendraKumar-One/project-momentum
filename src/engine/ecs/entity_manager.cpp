#include "engine/ecs/entity_manager.hpp"
#include <cassert>

EntityManager::EntityManager()
    : i_activeEntities_(0), i_nextFreeEntity_(0), i_entitiesLeft_(0x10000)
{
    b_isActiveFlags_.reset();
    v_entities_ = new uint16_t[0xFFF];

    for (size_t i = 0; i < 0xFFF; ++i)
    {
        v_entities_[i] = i + 1;
    }

    v_entities_[0xFFF] = 0xFFF;
}

EntityManager::~EntityManager()
{
    delete[] v_entities_;
}

entity EntityManager::Create()
{
    assert(i_entitiesLeft_ > 0 && "Entity pool exhausted");
    assert(i_activeEntities_ <= 0x1000 && "Entity pool exhausted");
    uint16_t index = i_nextFreeEntity_, gen = GetEntityGeneration(v_entities_[i_nextFreeEntity_]);
    i_nextFreeEntity_ = GetEntityIndex(v_entities_[i_nextFreeEntity_]);
    b_isActiveFlags_.set(index);
    ++i_activeEntities_;
    --i_entitiesLeft_;

    return GenerateEntity(index, gen);
}

void EntityManager::Destroy(entity ent)
{
    if (!IsActive(ent))
        return;

    --i_activeEntities_;
    uint16_t provided_index = GetEntityIndex(ent);
    b_isActiveFlags_.reset(provided_index);

    uint16_t provided_generation = GetEntityGeneration(v_entities_[provided_index]);

    if (provided_generation <= 14)
    {
        uint16_t replace_provided_index = GenerateEntity(i_nextFreeEntity_, provided_generation + 1);
        v_entities_[provided_index] = replace_provided_index;

        i_nextFreeEntity_ = provided_index;
    }
}

bool EntityManager::IsActive(entity ent)
{
    uint16_t provided_index = GetEntityIndex(ent);
    uint16_t provided_generation = GetEntityGeneration(ent);
    return (provided_generation == GetEntityGeneration(v_entities_[provided_index])) && b_isActiveFlags_.test(GetEntityIndex(ent));
}