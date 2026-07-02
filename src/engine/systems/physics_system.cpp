#include "engine/ecs/registry.hpp"
#include "engine/systems/physics_system.hpp"

void PhysicsSystem::update(Registry& reg, float dt)
{
    auto physics_view = reg.GetView<_Transform, _RigidBody>();

    for(entity ent : physics_view)
    {
        auto transform = reg.GetComponent<_Transform>(ent);
        auto rigid_body = reg.GetComponent<_RigidBody>(ent);

        
    }
}