#pragma once

#include <vector>

inline size_t interpolation_search(const std::vector<int>& data, const int& target)
{
    int low = 0;
    int high = (int)data.size() - 1;

    while (low <= high && target >= data[low] && target <= data[high])
    {
        if (data[low] == data[high])
            return data[low] == target ? low : NOT_FOUND;

        int pos = low + (long long)(high - low) * ((long long)target - data[low])
                      / ((long long)data[high] - data[low]);

        if (data[pos] == target)
            return pos;
        if (data[pos] < target)
            low = pos + 1;
        else
            high = pos - 1;
    }
    return NOT_FOUND;
}
