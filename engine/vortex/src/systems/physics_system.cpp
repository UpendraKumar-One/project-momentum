#include "vortex/ecs/registry.hpp"
#include "vortex/systems/physics_system.hpp"
#include <algorithm>

namespace Vortex::Systems
{
    PhysicsSystem::PhysicsSystem(float gravity)
        : GRAVITY(gravity)
    {
    }

    void PhysicsSystem::update(Ecs::Registry& reg, float dt)
    {
        auto physics_view = reg.GetView<Components::_Transform, Components::_RigidBody>();

        for(Ecs::entity ent : physics_view)
        {
            auto& transform = reg.GetComponent<Components::_Transform>(ent);
            auto& rigid_body = reg.GetComponent<Components::_RigidBody>(ent);

            if(rigid_body.b_isKinematic) // for entities that don't follow standard physics
                continue;

            transform.f_prev_x = transform.f_x;
            transform.f_prev_y = transform.f_y;

            rigid_body.f_velocity_x += (rigid_body.f_acceleration_x) * dt;
            rigid_body.f_velocity_y += (GRAVITY * rigid_body.f_gravityScale + rigid_body.f_acceleration_y) * dt;

            if((rigid_body.collisionFlags & Components::TOUCHING_DOWN) && (rigid_body.f_velocity_x != 0.0f))
            {
                float frictionStep = rigid_body.f_friction * GRAVITY * dt;

                if(abs(rigid_body.f_velocity_x) <= frictionStep)
                    rigid_body.f_velocity_x = 0.0f;

                else
                {
                    short int sign = (rigid_body.f_velocity_x > 0.0f)? 1 : -1;
                    rigid_body.f_velocity_x -= sign * frictionStep;
                }
            }

            if(rigid_body.collisionFlags == Components::NONE)
            {
                rigid_body.f_velocity_x *= (1.0f - (rigid_body.f_drag * dt));
                rigid_body.f_velocity_y *= (1.0f - (rigid_body.f_drag * dt));
            }

            rigid_body.f_velocity_x = std::clamp(rigid_body.f_velocity_x, -rigid_body.f_maxVelocity_x, rigid_body.f_maxVelocity_x);
            rigid_body.f_velocity_y = std::clamp(rigid_body.f_velocity_y, -rigid_body.f_maxVelocity_y, rigid_body.f_maxVelocity_y);

            transform.f_x += rigid_body.f_velocity_x * dt;
            transform.f_y += rigid_body.f_velocity_y * dt;

            rigid_body.f_acceleration_x = 0.0f;
            rigid_body.f_acceleration_y = 0.0f;
        }
    }
}