#pragma once

#include <vector>
#include <cstddef>
#include "Participants.h"

inline size_t interpolation_search(const std::vector<int>& data, const int& target)
{
    if (data.empty())
        return NOT_FOUND;

    size_t low = 0;
    size_t high = data.size() - 1;

    while (low <= high && target >= data[low] && target <= data[high])
    {
        if (data[low] == data[high])
            return (data[low] == target) ? low : NOT_FOUND;

        long long diff_target = static_cast<long long>(target) - data[low];
        long long diff_range  = static_cast<long long>(data[high]) - data[low];
        size_t pos = low + static_cast<size_t>(
            static_cast<double>(high - low) * static_cast<double>(diff_target)
            / static_cast<double>(diff_range));

        if (pos > high) pos = high;

        if (data[pos] == target)
            return pos;

        if (data[pos] < target)
            low = pos + 1;
        else
        {
            if (pos == 0) break;
            high = pos - 1;
        }
    }
    return NOT_FOUND;
}
