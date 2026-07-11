#pragma once

#include "vortex/ecs/entity.hpp"

namespace vortex::ecs { class VxRegistry; }

namespace entity_factory
{
    vortex::ecs::VxEntity createPlayer(vortex::ecs::VxRegistry& reg);
}