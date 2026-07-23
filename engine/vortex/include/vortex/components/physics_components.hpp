#pragma once

#include <cstdint>
#include "vortex/core/math/vortex_math.hpp"

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

    enum class ECollisionShape : uint8_t
    {
        None = 0,
        Circle = 1,
        AABB = 2,
        OBB = 3,
        Polygon = 4
    };

    enum class ERigidBodyType : uint8_t
    {
        Static = 0,
        Kinematic = 1,
        Dynamic = 2
    };

    struct VxTransformComponent
    {
        math::VxVec2 curr_pos;
        math::VxVec2 prev_pos; // Useful for interpolation / sub-stepping
        float rotation;
    };

    struct VxColliderComponent
    {
        // --- Shape Geometry ---
        ECollisionShape shape_type;

        union ShapeData
        {
            struct
            {
                math::VxVec2 offset;
                float radius;
            } circle;

            struct
            {
                math::VxVec2 offset;
                math::VxVec2 half_extents;
            } aabb;

            // OBB and Polygon data can be added here later
        } shape;

        // --- Surface Properties ---
        float friction;    // 0.0 = ice, 1.0 = rubber
        float restitution; // 0.0 = clay, 1.0 = superball
        bool is_sensor;    // True = trigger zones (no physical response)

        // --- Collision Filtering ---
        uint16_t collision_layer;
        uint16_t collision_mask;
    };

    struct VxRigidBodyComponent
    {
        ERigidBodyType body_type;

        // --- Inertial Properties ---
        float mass;
        float inverse_mass;    // 1.0 / mass. 0.0 for static bodies.
        float inverse_inertia; // 1.0 / moment_of_inertia. 0.0 for static.

        // --- Motion State ---
        math::VxVec2 velocity;
        float angular_velocity;

        // --- Damping & Config ---
        float linear_damping;
        float angular_damping;
        float gravity_scale; // Usually 1.0, but allows anti-gravity or heavy objects

        // --- Sleep State ---
        float sleep_timer;
        bool is_awake;
        bool use_ccd; // Continuous Collision Detection flag
    };

    struct VxForceAccumulatorComponent
    {
        math::VxVec2 net_force;
        float net_torque;
    };

    struct VxCollisionStateComponent
    {
        uint8_t collision_flags;
    };
}