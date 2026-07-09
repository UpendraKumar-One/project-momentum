#pragma once

#include "raylib.h"

namespace vortex::components
{
    struct SpriteComponent
    {
        Texture2D* img_texture;

        Rectangle src_rectangle;

        Color tint;

        int z_index;
    };
}