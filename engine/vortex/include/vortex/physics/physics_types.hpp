#pragma once

#include "vortex/core/config/vortex_config.hpp"
#include "vortex/core/math/vortex_math.hpp"
#include "vortex/core/containers/static_array.hpp"

namespace vortex::physics
{
    using VxEntity = vortex::config::VxEntity;

    struct VxCollisionPair
    {
        VxEntity entity_a, entity_b;
    };

    struct VxContactPoint
    {
        vortex::math::VxVec2 position;
        float penetration_depth;
    };

    struct VxContactManifold
    {
        VxEntity entity_a, entity_b;
        vortex::math::VxVec2 normal;
        vortex::containers::VxStaticArray<VxContactPoint, 2> points;
    };
}
