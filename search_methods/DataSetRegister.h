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
	//datastack.push({"description", ReadFile("datasets/dataset's name") })
	return datastack;
}
