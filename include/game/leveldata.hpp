#pragma once

#include "raylib.h"
#include <string>
#include "lazy_array.hpp"

struct TileSet
{
    int firstGID;
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