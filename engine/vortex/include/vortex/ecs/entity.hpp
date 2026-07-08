#pragma once

#include <cstdint>

namespace Vortex::Ecs
{
    using entity = uint16_t;

    constexpr uint16_t INDEX_BITS = 12;
    constexpr uint16_t INDEX_MASK = (1 << INDEX_BITS) - 1;

    constexpr uint16_t GENERATION_BITS = 4;
    constexpr uint16_t GENERATION_MASK = ((1 << GENERATION_BITS) - 1) << INDEX_BITS;

    constexpr uint16_t MAX_ENTITIES = 0x1000;

    inline uint16_t GetEntityIndex(entity ent)
    {
        return ent & INDEX_MASK;
    }

    inline uint16_t GetEntityGeneration(entity ent)
    {
        return (ent & GENERATION_MASK) >> INDEX_BITS;
    }

    inline entity GenerateEntity(uint16_t index, uint16_t generation)
    {
        return (generation << INDEX_BITS) | index;
    }
}