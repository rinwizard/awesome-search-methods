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
	datastack.push({ "100 int sorted", ReadFile("int_100.txt"), 19090 });
	datastack.push({ "1000 int sorted", ReadFile("int_1000.txt"), 21060 });
	datastack.push({ "10000 int sorted", ReadFile("int_10000.txt"), 19784 });
	datastack.push({ "100000 int sorted", ReadFile("int_100000.txt"), 18649 });
	datastack.push({ "1000000 int sorted", ReadFile("int_1000000.txt"), 999889107 });
	datastack.push({ "10000 int unsorted",ReadFile("comm_data_unsorted.txt"), 2 });
	datastack.push({ "Ternary best", ReadFile("ternary_best.txt"), 333 });
	datastack.push({ "Ternary average", ReadFile("ternary_average.txt"), 1500 });
	datastack.push({ "Ternary worst", ReadFile("ternary_worst.txt"), 2001 });
	datastack.push({ "Hash Worst  (10)", ReadFile("hash_worst.txt"), 5 });
	datastack.push({ "Hash Average (500)", ReadFile("hash_avg.txt"), 250 });
	datastack.push({ "Hash Best (2000)", ReadFile("hash_best.txt"), 42 });
	datastack.push({ "Skip Best (10000)", ReadFile("skip_best.txt"), 23502 });
	datastack.push({ "Skip Avg (100000)", ReadFile("skip_average.txt"), 164333 });
	datastack.push({ "Skip Worst (1M)", ReadFile("skip_worst.txt"), 103994 });
	datastack.push({ "Jump Best", ReadFile("comm_data_sorted.txt"), 10 });
    datastack.push({ "Jump Average", ReadFile("comm_data_sorted.txt"), 1610 });
    datastack.push({ "Jump Worst", ReadFile("comm_data_sorted.txt"), 99999 });
	datastack.push({ "Interpolation best", ReadFile("interpolation_best.txt"), 1501 });
	datastack.push({ "Interpolation best", ReadFile("interpolation_average.txt"), 492871 });
	datastack.push({ "Interpolation best", ReadFile("interpolation_worst.txt"), 998 });
	datastack.push({ "Exponential best", ReadFile("exponential_best.txt"), 139 });
	datastack.push({ "Exponential avg", ReadFile("exponential_average.txt"), 24675 });
	datastack.push({ "Exponential worst", ReadFile("exponential_worst.txt"), 2000000000 });
	return datastack;
}
