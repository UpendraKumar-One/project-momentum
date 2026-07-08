#include "game/entity_factory.hpp"
#include "engine/ecs/registry.hpp"

namespace EntityFactory
{
    entity CreatePlayer(Registry& reg)
    {
        entity player = reg.CreateEntity();


        return player;
    }
}