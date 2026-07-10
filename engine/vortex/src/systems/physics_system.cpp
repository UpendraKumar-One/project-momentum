#include "vortex/ecs/registry.hpp"
#include "vortex/systems/physics_system.hpp"
#include <algorithm>
#include <cmath>

using namespace vortex;

namespace vortex::systems
{
    VxPhysicsSystem::VxPhysicsSystem(float gravity)
        : m_gravity(gravity)
    {
    }

    void VxPhysicsSystem::dynamicsUpdate(ecs::VxRegistry& reg, float dt)
    {
        auto dynamics_view = reg.getView<components::VxDynamicsComponent, components::VxVelocityComponent>();

        for(ecs::VxEntity ent : dynamics_view)
        {
            auto& dynamics = reg.getComponent<components::VxDynamicsComponent>(ent);
            auto& velocity = reg.getComponent<components::VxVelocityComponent>(ent);

            // Add gravity force to the accumulator
            dynamics.net_force_y += (m_gravity * dynamics.gravity_scale * dynamics.mass);

            // Calculate Acceleration (a = F * 1/m)
            float accel_x = dynamics.net_force_x * dynamics.inv_mass;
            float accel_y = dynamics.net_force_y * dynamics.inv_mass;

            // Add to Velocity (v = v + a*dt)
            velocity.x += accel_x * dt;
            velocity.y += accel_y * dt;

            // Apply universal damping (drag/air resistance)
            velocity.x *= (1.0f - (dynamics.linear_damping * dt));
            velocity.y *= (1.0f - (dynamics.linear_damping * dt));

            // Clamp to max velocity
            velocity.x = std::clamp(velocity.x, -velocity.max_x, velocity.max_x);
            velocity.y = std::clamp(velocity.y, -velocity.max_y, velocity.max_y);

            // Reset the accumulator for the next frame
            dynamics.net_force_x = 0.0f;
            dynamics.net_force_y = 0.0f;
        }
    }

    void VxPhysicsSystem::kinematicsUpdate(ecs::VxRegistry& reg, float dt)
    {
        auto movement_view = reg.getView<components::VxTransformComponent, components::VxVelocityComponent>();

        for(ecs::VxEntity ent : movement_view)
        {
            auto& transform = reg.getComponent<components::VxTransformComponent>(ent);
            auto& velocity = reg.getComponent<components::VxVelocityComponent>(ent);

            // Store previous position for rendering interpolation or swept collision fallback
            transform.prev_x = transform.x;
            transform.prev_y = transform.y;

            // Apply final, collision-checked velocity to transform
            transform.x += velocity.x * dt;
            transform.y += velocity.y * dt;
        }
    }
}