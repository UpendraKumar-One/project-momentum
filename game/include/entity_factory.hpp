#pragma once

#include "vortex/ecs/entity.hpp"

namespace vortex::ecs { class Registry; }

namespace entity_factory
{
    vortex::ecs::Entity createPlayer(vortex::ecs::Registry& reg);
}