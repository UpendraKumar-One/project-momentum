#include "game/entity_factory.hpp"
#include "vortex/ecs/registry.hpp"

namespace entity_factory
{
    vortex::ecs::Entity createPlayer(vortex::ecs::Registry& reg)
    {
        vortex::ecs::Entity player = reg.createEntity();


        return player;
    }
}