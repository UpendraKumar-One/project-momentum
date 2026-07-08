#pragma once

#include "raylib.h"

namespace Vortex::Components
{
    struct _Sprite
    {
        Texture2D* imgTexture;

        Rectangle srcRectangle;

        Color tint;

        int i_zIndex;
    };
}