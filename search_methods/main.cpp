#include <vector>
#include <chrono>
#include <algorithm>
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include <iomanip> 
#include "DataSetRegister.h"
#include "Interpolationsearch.h"
#include "HashTable.h"
#include "Participants.h"
#include "SkipList.h"
#include "TernarySearch.h"
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

    auto time = chrono::duration_cast<chrono::nanoseconds>(stop - start).count();

    bool get_res = (res != NOT_FOUND) && (res < data.size() && data[res] == target);

    ostringstream oss{};
    oss << "\"" << left << setw(18) << dataset << "\" "
        << setw(10) << right << data.size() << "  "
        << setw(20) << left << team << "  "
        << setw(25) << left << ParseName(method_name) << "  "
        << (get_res ? to_string(time) : "-1");

    logs.push_back(oss.str());
}

int main()
{
    cout << endl << "**************INTEGER SEARCH RACE**************" << endl << endl;

    cout << "\"" << left << setw(18) << "Dataset" << "\" "
        << setw(10) << right << "Size" << "  "
        << setw(20) << left << "Team" << "  "
        << setw(25) << left << "Method" << "  "
        << "Time (ns)" << endl;

    auto DataSets = GenerateDataSets();
    while (!DataSets.empty())
    {
        auto& ds = DataSets.top();
        dataset = ds.description;
        const auto& data = ds.data;

        if (data.empty()) { DataSets.pop(); continue; }
        const int target = ds.target;

        team = "Skip List";
        RUN(skip_list_search);
        team = "Interpolation Search";
        RUN(interpolation_search);
        team = "Ternary Search";
		RUN(ternary_search);
        team = "Hash Table method";
        RUN(hash_search);
        DataSets.pop();
    }

    for (auto& s : logs)
        cout << s << endl;

    ofstream fout("release.txt");
    for (auto& s : logs)
        fout << s << endl;
}