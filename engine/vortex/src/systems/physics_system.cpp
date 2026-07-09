#include "vortex/ecs/registry.hpp"
#include "vortex/systems/physics_system.hpp"
#include <algorithm>
#include <cmath>

namespace vortex::systems
{
    PhysicsSystem::PhysicsSystem(float gravity)
        : m_gravity(gravity)
    {
    }

    void PhysicsSystem::update(ecs::Registry& reg, float dt)
    {
        auto physics_view = reg.getView<components::TransformComponent, components::RigidBodyComponent>();

        for(ecs::Entity ent : physics_view)
        {
            auto& transform = reg.getComponent<components::TransformComponent>(ent);
            auto& rigid_body = reg.getComponent<components::RigidBodyComponent>(ent);

            if(rigid_body.is_kinematic) // for entities that don't follow standard physics
                continue;

            transform.prev_x = transform.x;
            transform.prev_y = transform.y;

            rigid_body.velocity_x += (rigid_body.acceleration_x) * dt;
            rigid_body.velocity_y += (m_gravity * rigid_body.gravity_scale + rigid_body.acceleration_y) * dt;

            if((rigid_body.collision_flags & components::TouchingDown) && (rigid_body.velocity_x != 0.0f))
            {
                float friction_step = rigid_body.friction * m_gravity * dt;

                if(std::abs(rigid_body.velocity_x) <= friction_step)
                    rigid_body.velocity_x = 0.0f;

                else
                {
                    short int sign = (rigid_body.velocity_x > 0.0f)? 1 : -1;
                    rigid_body.velocity_x -= sign * friction_step;
                }
            }

            if(rigid_body.collision_flags == components::None)
            {
                rigid_body.velocity_x *= (1.0f - (rigid_body.drag * dt));
                rigid_body.velocity_y *= (1.0f - (rigid_body.drag * dt));
            }

            rigid_body.velocity_x = std::clamp(rigid_body.velocity_x, -rigid_body.max_velocity_x, rigid_body.max_velocity_x);
            rigid_body.velocity_y = std::clamp(rigid_body.velocity_y, -rigid_body.max_velocity_y, rigid_body.max_velocity_y);

            transform.x += rigid_body.velocity_x * dt;
            transform.y += rigid_body.velocity_y * dt;

            rigid_body.acceleration_x = 0.0f;
            rigid_body.acceleration_y = 0.0f;
        }
    }
}