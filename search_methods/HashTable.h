#pragma once
#include <vector>
#include <cstddef>
#include <utility>
#include <cmath>

inline bool isPrime(int n) {
	if (n <= 1) return false;
	if (n == 2) return true;
	if (n % 2 == 0) return false;
	for (int i = 3; i * i <= n; i += 2) {
		if (n % i == 0) return false;
	}
	return true;
}

inline int findNextPrime(int n) {
	while (true) {
		if (isPrime(n)) return n;
		n++;
	}
}

struct HashTable {
	std::vector<std::vector<std::pair<int, std::size_t>>> buckets;
	int tableSize;

	HashTable(int requestedSize) {
		tableSize = findNextPrime(requestedSize);
		buckets.resize(tableSize);
	}

	int getHash(int key) {
		return std::abs(key) % tableSize;
	}

	void insert(int key, std::size_t index) {
		int hashIndex = getHash(key);
		buckets[hashIndex].push_back({ key, index });
	}

	std::size_t getIndex(int key) {
		int hashIndex = getHash(key);
		for (std::size_t i = 0; i < buckets[hashIndex].size(); i++) {
			if (buckets[hashIndex][i].first == key) {
				return buckets[hashIndex][i].second;
			}
		}
		return static_cast<std::size_t>(-1);
	}
};

inline std::size_t hash_search(const std::vector<int>& data, const int& target) {
	if (data.empty()) return static_cast<std::size_t>(-1);

	int size = data.size() * 2;
	HashTable table(size);

	for (std::size_t i = 0; i < data.size(); i++) {
		table.insert(data[i], i);
	}

	return table.getIndex(target);
}