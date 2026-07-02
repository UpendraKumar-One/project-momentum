#pragma once

#include "raylib.h"

struct _Sprite
{
    Texture2D* imgTexture;

    Rectangle srcRectangle;

    Color tint;

    int i_zIndex;
};