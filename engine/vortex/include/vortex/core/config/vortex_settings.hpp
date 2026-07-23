#pragma once
#include "vortex/core/math/vortex_math.hpp"

namespace vortex::config 
{
    struct PhysicsSettings 
    {
        math::VxVec2 gravity = { 0.0f, -9.81f };
        int velocity_iterations = 8;
        int position_iterations = 3;
        float sleep_velocity_threshold = 0.1f;
    };

    class VxEngineSettings 
    {
    public:
        // Future: static void loadFromJson(const char* filepath); 
        
        inline static PhysicsSettings physics;
    };
}
