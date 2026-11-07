#pragma once
#include <string>
#include <stack>
#include <vector>
#include <fstream>


template <typename T>
struct DataSet
{
	std::string description;
	std::vector<T> data;
	T target;
};

inline std::vector<int> ReadFile(const std::string& path)
{
	std::ifstream fin(path);
	if (!fin)
		return {}; // error
	std::vector<int> v;
	int x;
	while (fin >> x)
		v.push_back(x);
	return v;
}

inline std::stack<DataSet<int>>  GenerateDataSets(){
	std::stack<DataSet<int>> datastack;
	//enter your datasets in format:
	datastack.push({ "10000 int sorted", ReadFile("comm_data_sorted.txt"), 22430 });
	datastack.push({ "10000 int unsorted",ReadFile("comm_data_unsorted.txt"), 2 });
	datastack.push({ "Hash Worst  (10)", ReadFile("hash_worst.txt"), 5 });
	datastack.push({ "Hash Average (500)", ReadFile("hash_avg.txt"), 250 });
	datastack.push({ "Hash Best (2000)", ReadFile("hash_best.txt"), 42 });
	datastack.push({ "Ternary best", ReadFile("ternary_best.txt"), 333 });
	datastack.push({ "Ternary average", ReadFile("ternary_average.txt"), 1500 });
	datastack.push({ "Ternary worst", ReadFile("ternary_worst.txt"), 2001 });
	return datastack;
}
