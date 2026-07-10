#pragma once

namespace vortex::ecs {
    class VxRegistry;
}

namespace vortex::systems
{
    class VxPhysicsSystem
    {
    public:
        VxPhysicsSystem(float gravity);
        
        // Pass 1: Integrate forces into intended velocity
        void dynamicsUpdate(ecs::VxRegistry& reg, float dt);

        // Pass 2: Integrate final velocity into position
        void kinematicsUpdate(ecs::VxRegistry& reg, float dt);

    private:
        float m_gravity;
    };
}