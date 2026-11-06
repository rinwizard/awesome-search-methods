#pragma once
#include <vector>
#include <cstddef>

inline size_t ternary_search(const std::vector<int>& data, const int& target)
{
    int left = 0;
    int right = data.size() - 1;

    while (left <= right)
    {
        int mid1 = left + (right - left) / 3;
        int mid2 = right - (right - left) / 3;
        if (data[mid1] == target)
            return mid1;
        if (data[mid2] == target)
            return mid2;
        if (target < data[mid1])
            right = mid1 - 1;
        else if (target > data[mid2])
            left = mid2 + 1;
        else
        {
            left = mid1 + 1;
            right = mid2 - 1;
        }
    }
    return static_cast<size_t>(-1);
}
