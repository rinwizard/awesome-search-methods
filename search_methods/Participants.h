#pragma once
#include <vector>
#include <cstddef>
constexpr std::size_t NOT_FOUND = static_cast<std::size_t>(-1);
#include "SkipList.h"
#include "Interpolationsearch.h"
#include "TernarySearch.h"
#include "HashTable.h"
#include "Exponential.h"
#include "JumpSearch.h"
//#include your .h file

// not found

template <typename T>
using Participant = std::size_t(*)(const std::vector<T>&, const T&);
