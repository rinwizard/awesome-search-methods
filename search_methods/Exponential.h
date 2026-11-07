#pragma once

#include <vector>
#include <cstddef>
#include <algorithm>

namespace exponential_search_detail
{
    inline std::size_t binarySearch(
        const std::vector<int>& data,
        std::size_t left,
        std::size_t right,
        int target)
    {
        while (left <= right)
        {
            std::size_t mid = left + (right - left) / 2;

            if (data[mid] == target)
            {
                return mid;
            }

            if (data[mid] < target)
            {
                left = mid + 1;
            }
            else
            {
                if (mid == 0)
                {
                    break;
                }
                right = mid - 1;
            }
        }

        return static_cast<std::size_t>(-1);
    }
}

inline std::size_t exponential_search(
    const std::vector<int>& data,
    const int& target)
{
    const std::size_t notFound = static_cast<std::size_t>(-1);

    if (data.empty())
    {
        return notFound;
    }

    if (data[0] == target)
    {
        return 0;
    }

    if (data[0] > target)
    {
        return notFound;
    }

    std::size_t bound = 1;

    while (bound < data.size() && data[bound] <= target)
    {
        bound *= 2;
    }

    std::size_t left = bound / 2;
    std::size_t right = std::min(bound, data.size() - 1);

    return exponential_search_detail::binarySearch(
        data,
        left,
        right,
        target);
}
