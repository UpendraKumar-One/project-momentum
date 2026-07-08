#pragma once

#include <cstdint>

namespace Vortex::Components
{
    enum CollisionFlags : uint8_t
    {
        NONE = 0,
        TOUCHING_UP = 1 << 0,
        TOUCHING_LEFT = 1 << 1,
        TOUCHING_DOWN = 1 << 2,
        TOUCHING_RIGHT = 1 << 3
    };

    struct _Transform
    {
        float f_x, f_y;
        float f_prev_x, f_prev_y;
        float f_rotation;
    };

    struct _RigidBody
    {
        float f_gravityScale;

        float f_velocity_x, f_velocity_y;
        float f_maxVelocity_x, f_maxVelocity_y;
        float f_acceleration_x, f_acceleration_y;

        float f_mass;
        float f_drag;
        float f_friction;

        bool b_isKinematic;
        uint8_t collisionFlags;
    };

    struct _HitBox
    {
        float f_width, f_height;
        float f_offsetTransform_x, f_offsetTransform_y;

        uint16_t collisionLayer, collisionMask;
    };
}