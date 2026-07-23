#pragma once
#include <cstdint>
#include <cstddef>

namespace vortex::config 
{
    // --- Core Types ---
    using VxEntity = uint16_t;

    // --- ECS Constants ---
    constexpr VxEntity MAX_ENTITIES = 0x1000;
    constexpr size_t MAX_COMPONENTS = 32;
    constexpr VxEntity NULL_ENTITY = 0xFFFF;

    // --- Entity ID Packing ---
    constexpr uint16_t ENTITY_INDEX_BITS = 12;
    constexpr VxEntity ENTITY_INDEX_MASK = (1 << ENTITY_INDEX_BITS) - 1;
    constexpr uint16_t ENTITY_GENERATION_BITS = 4;
    constexpr VxEntity ENTITY_GENERATION_MASK = ((1 << ENTITY_GENERATION_BITS) - 1) << ENTITY_INDEX_BITS;

    // --- Renderer Constants ---
    constexpr size_t MAX_RENDER_COMMANDS = 10000;

    // --- Physics Constants ---
    constexpr size_t BROAD_HASH_TABLE_SIZE = 1024; // How many buckets the grid hash table can have
    constexpr size_t MAX_ENTITIES_PER_CELL = 16; // how many entities can be recorded for collision in a single cell
}
