#pragma once

#include <algorithm>
#include <cmath>

namespace vortex::utils
{
    // --- Math & Bounds ---

    template <typename T>
    constexpr const T& min(const T& a, const T& b)
    {
        return std::min(a, b);
    }

    template <typename T>
    constexpr const T& max(const T& a, const T& b)
    {
        return std::max(a, b);
    }

    template <typename T>
    constexpr const T& clamp(const T& v, const T& lo, const T& hi)
    {
        return std::clamp(v, lo, hi);
    }

    template <typename T>
    constexpr T abs(T v)
    {
        return std::abs(v);
    }

    // --- Searching & Sorting ---

    template <typename RandomIt>
    void sort(RandomIt first, RandomIt last)
    {
        std::sort(first, last);
    }

    template <typename RandomIt, typename Compare>
    void sort(RandomIt first, RandomIt last, Compare comp)
    {
        std::sort(first, last, comp);
    }

    template <typename InputIt, typename T>
    InputIt find(InputIt first, InputIt last, const T& value)
    {
        return std::find(first, last, value);
    }

    template <typename InputIt, typename UnaryPredicate>
    InputIt findIf(InputIt first, InputIt last, UnaryPredicate p)
    {
        return std::find_if(first, last, p);
    }
}
