#pragma once

#include "raylib.h"
#include <string>
#include "vortex/core/containers/vortex_array.hpp"

struct TileSet
{
    int first_gid;
    std::string name;
    int tile_height;
    int tile_width;
    Texture2D texture;
};

struct TileLayer
{
    std::string name;
    bool is_visible;
};