#pragma once
#include <vector>
#include <cstddef>
//#include your .h file

// not found
constexpr std::size_t NOT_FOUND = static_cast<std::size_t>(-1);
// if found -- answer is the index
// all errors will log as "-1".

template <typename T>
using Participant = std::size_t(*)(const std::vector<T>&, const T&);

// example
std::size_t linear_search_by_std(const std::vector<int>& data, const int& target);

//--------------------Index Search---------------------------
//insert yours like the example
//---------------------------------------------------------------
