#pragma once

#include <cstdint>

namespace vortex::components
{
    enum CollisionFlags : uint8_t
    {
        None = 0,
        TouchingUp = 1 << 0,
        TouchingLeft = 1 << 1,
        TouchingDown = 1 << 2,
        TouchingRight = 1 << 3
    };

    struct TransformComponent
    {
        float x, y;
        float prev_x, prev_y;
        float rotation;
    };

    struct RigidBodyComponent
    {
        float gravity_scale;

        float velocity_x, velocity_y;
        float max_velocity_x, max_velocity_y;
        float acceleration_x, acceleration_y;

        float mass;
        float drag;
        float friction;

        bool is_kinematic;
        uint8_t collision_flags;
    };

    struct HitBoxComponent
    {
        float width, height;
        float offset_transform_x, offset_transform_y;

        uint16_t collision_layer, collision_mask;
    };
}