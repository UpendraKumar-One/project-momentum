#include "momentum/entity_factory.hpp"
#include "vortex/ecs/registry.hpp"

namespace entity_factory
{
    vortex::ecs::VxEntity createPlayer(vortex::ecs::VxRegistry& reg)
    {
        vortex::ecs::VxEntity player = reg.createEntity();


        return player;
    }
}