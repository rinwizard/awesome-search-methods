#include <vector>
#include <chrono>
#include <algorithm>
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include "DataSetRegister.h"
#include "Participants.h"
#include "SkipList.h"
#include <regex>

using namespace std;

string ParseName(string& method_name)
{
    transform(method_name.begin(), method_name.end(), method_name.begin(),
        [](unsigned char c) { return std::tolower(c); });

    auto res = regex_replace(method_name, std::regex("_by_"), "\t");
    if (res.length() == method_name.length())
    {
        res = regex_replace(res, std::regex("by"), "\t");
        if (res.length() == method_name.length())
            res = regex_replace(res, std::regex("_"), "\t");
    }
    return res;
}

//meowmewo
#define RUN(x) { Run(#x, x, data, target); }


static string team = "";
static string dataset = "";
static vector<string> logs;

template <typename T>
void Run(string method_name, Participant<T> p, const vector<T>& data, const T& target)
{
    auto start = chrono::system_clock::now();
    size_t res = p(data, target);
    auto stop = chrono::system_clock::now();
    auto time = chrono::duration_cast<chrono::microseconds>(stop - start).count();

    bool get_res = (res == NOT_FOUND) || (res < data.size() && data[res] == target);
    ostringstream oss{};
    oss << "\"" << dataset << "\"\t"
        << data.size() << "\t"
        << team << "\t"
        << ParseName(method_name) << "\t"
        << (get_res ? to_string(time) : "-1");
    logs.push_back(oss.str());
}

int main()
{
    std::vector<int> data = { 10, 20, 40, 5, 3, 1, 7, 15, 8, 30 };

    std::cout << "Search 7: "
        << skip_list_search(data, 7) << std::endl;

    std::cout << "Search 30: "
        << skip_list_search(data, 30) << std::endl;

    std::cout << "Search 100: "
        << skip_list_search(data, 100) << std::endl;

    return 0;
}