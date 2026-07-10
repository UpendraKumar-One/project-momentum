#pragma once

#include <cstdint>

namespace vortex::components
{
    enum ECollisionFlags : uint8_t
    {
        None = 0,
        TouchingUp = 1 << 0,
        TouchingLeft = 1 << 1,
        TouchingDown = 1 << 2,
        TouchingRight = 1 << 3
    };

    struct VxTransformComponent
    {
        float x, y;
        float prev_x, prev_y;
        float rotation;
    };

    struct VxVelocityComponent
    {
        float x, y;
        float max_x, max_y;
    };

    struct VxDynamicsComponent
    {
        float net_force_x, net_force_y;

        float mass;
        float inv_mass;
        
        float linear_damping;
        float gravity_scale;
    };

    struct VxHitBoxComponent
    {
        float width, height;
        float offset_transform_x, offset_transform_y;

        uint16_t collision_layer, collision_mask;
    };

    struct VxCollisionStateComponent
    {
        uint8_t collision_flags;
    };
}