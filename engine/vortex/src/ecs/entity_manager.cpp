#include "vortex/ecs/entity_manager.hpp"
#include <cassert>

namespace vortex::ecs
{
    EntityManager::EntityManager()
        : m_activeEntities(0), m_nextFreeEntity(0), m_entitiesLeft(0x10000)
    {
        m_isActiveFlags.reset();
        m_entities = new uint16_t[0xFFF];

        for (size_t i = 0; i < 0xFFF; ++i)
        {
            m_entities[i] = i + 1;
        }

        m_entities[0xFFF] = 0xFFF;
    }

    EntityManager::~EntityManager()
    {
        delete[] m_entities;
    }

    Entity EntityManager::create()
    {
        assert(m_entitiesLeft > 0 && "Entity pool exhausted");
        assert(m_activeEntities <= 0x1000 && "Entity pool exhausted");
        uint16_t index = m_nextFreeEntity, gen = getEntityGeneration(m_entities[m_nextFreeEntity]);
        m_nextFreeEntity = getEntityIndex(m_entities[m_nextFreeEntity]);
        m_isActiveFlags.set(index);
        ++m_activeEntities;
        --m_entitiesLeft;

        return generateEntity(index, gen);
    }

    void EntityManager::destroy(Entity ent)
    {
        if (!isActive(ent))
            return;

        --m_activeEntities;
        uint16_t provided_index = getEntityIndex(ent);
        m_isActiveFlags.reset(provided_index);

        uint16_t provided_generation = getEntityGeneration(m_entities[provided_index]);

        if (provided_generation <= 14)
        {
            uint16_t replace_provided_index = generateEntity(m_nextFreeEntity, provided_generation + 1);
            m_entities[provided_index] = replace_provided_index;

            m_nextFreeEntity = provided_index;
        }
    }

    bool EntityManager::isActive(Entity ent)
    {
        uint16_t provided_index = getEntityIndex(ent);
        uint16_t provided_generation = getEntityGeneration(ent);
        return (provided_generation == getEntityGeneration(m_entities[provided_index])) && m_isActiveFlags.test(getEntityIndex(ent));
    }
}