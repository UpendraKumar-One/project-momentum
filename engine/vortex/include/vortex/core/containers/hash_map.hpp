#pragma once

#include <unordered_map>

namespace vortex::containers
{
    template <typename K, typename V>
    using VHashMap = std::unordered_map<K, V>;
}