#pragma once

#include <unordered_map>

namespace vortex::core::containers
{
    template <typename K, typename V>
    using HashMap = std::unordered_map<K, V>;
}