#pragma once

namespace Vortex::Ecs {
    class Registry;
}

namespace Vortex::Systems
{
    class PhysicsSystem
    {
    public:
        PhysicsSystem(float gravity);
        void update(Vortex::Ecs::Registry& reg, float dt);

    private:
        float GRAVITY;
    };
}