#pragma once

namespace Vortex::Renderer
{
    struct Color
    {
        unsigned char r, g, b, a;
    };

    struct Texture2D
    {
        unsigned int id;
        int width, height;
        int mipmaps;
        int format;   
    };
}