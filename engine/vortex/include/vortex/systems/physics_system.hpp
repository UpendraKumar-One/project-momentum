#pragma once

namespace vortex::ecs {
    class Registry;
}

namespace vortex::systems
{
    class PhysicsSystem
    {
    public:
        PhysicsSystem(float gravity);
        void update(ecs::Registry& reg, float dt);

    private:
        float m_gravity;
    };
}