#pragma once

#include <vector>
#include <stack>
#include <cstddef>
#include <cmath>
#include <algorithm>
#include "Participants.h"

inline size_t jump_search(const std::vector<int>& data, const int& target)
{
    if (data.empty())
        return NOT_FOUND;

    size_t n = data.size();
    size_t step = static_cast<size_t>(std::sqrt(static_cast<double>(n)));
    if (step == 0)
        step = 1;

    size_t prev = 0;
    size_t curr = std::min(step, n) - 1;

    while (data[curr] < target)
    {
        prev = curr + 1;
        curr = std::min(curr + step, n - 1);
        if (prev >= n)
            return NOT_FOUND;
        if (curr == n - 1 && data[curr] < target)
            return NOT_FOUND;
    }

    for (size_t i = prev; i <= curr && i < n; ++i)
    {
        if (data[i] == target)
            return i;
        if (data[i] > target)
            break;
    }

    return NOT_FOUND;
}
