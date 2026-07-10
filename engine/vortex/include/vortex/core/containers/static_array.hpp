#pragma once

#include <array>

namespace vortex::containers
{
    template <typename T, size_t N>
    using VxStaticArray = std::array<T, N>;
}