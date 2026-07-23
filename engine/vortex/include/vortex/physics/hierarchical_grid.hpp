#pragma once

#include "vortex/core/containers/static_array.hpp"
#include "vortex/core/containers/vortex_array.hpp"
#include "vortex/core/config/vortex_config.hpp"
#include "vortex/core/math/vortex_aabb.hpp"
#include "vortex/physics/physics_types.hpp"

namespace vortex::physics
{
    // This is the max number of entities that can be recorded in a single grid cell
    struct CollisionBucket
    {
        vortex::containers::VxStaticArray<vortex::config::VxEntity, vortex::config::MAX_ENTITIES_PER_CELL> bucket;
    };

    // Struct defining the grid level(size)
    struct GridLevel
    {
        float cell_size;
        vortex::containers::VxStaticArray<CollisionBucket, vortex::config::BROAD_HASH_TABLE_SIZE> grid_hash;
    };

    class VxHGrid
    {
    public:
        VxHGrid(vortex::containers::VxArray<size_t>);
        ~VxHGrid() = default;

        void clear(); // to clear the hash table at the beginning of every frame

        void insert(vortex::config::VxEntity, vortex::math::VxAABB); // hash an entity according to it's current AABB

        void generatePairs(vortex::containers::VxArray<vortex::physics::VxCollisionPair>&); // writes to the out_pairs array for the narrow phase

    private:
        vortex::containers::VxArray<GridLevel> m_levelGrid;
    };
}