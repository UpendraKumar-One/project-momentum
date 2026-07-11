#pragma once

#include "vortex/renderer/vortex_graphics.hpp"
#include <string>
#include "vortex/core/containers/vortex_array.hpp"

struct TileSet
{
    int first_gid;
    std::string name;
    int tile_height;
    int tile_width;
    vortex::renderer::VxTexture texture;
};

struct TileLayer
{
    std::string name;
    bool is_visible;
};