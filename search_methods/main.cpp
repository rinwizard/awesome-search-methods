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
#include "JumpSearch.h"
#include <regex>

using namespace std;

string ParseName(string& method_name)
{
    transform(method_name.begin(), method_name.end(), method_name.begin(),
        [](unsigned char c) { return std::tolower(c); });

    auto res = regex_replace(method_name, std::regex("_by_"), " ");
    if (res.length() == method_name.length())
    {
        res = regex_replace(res, std::regex("by"), " ");
        if (res.length() == method_name.length())
            res = regex_replace(res, std::regex("_"), " ");
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
        << left << setw(10) << data.size() << "  "
        << left << setw(20) << team << "  "
        << left << setw(25) << ParseName(method_name) << "  "
        << left << setw(12) << (get_res ? time : -1);

    logs.push_back(oss.str());
}

int main()
{
    cout << endl << "**************INTEGER SEARCH RACE**************" << endl << endl;

    cout << "\"" << left << setw(18) << "Dataset" << "\" "
        << left << setw(10) << "Size" << "  "
        << left << setw(20) << "Team" << "  "
        << left << setw(25) << "Method" << "  "
        << left << setw(12) << "Time (ns)" << endl;

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
        team = "Hash Table Method";
        RUN(hash_search);
        team = "Exponential Search";
        RUN(exponential_search);
        team = "Jump Search";
        RUN(jump_search);
        DataSets.pop();
    }

    for (auto& s : logs)
        cout << s << endl;

    ofstream fout("release.txt");
    for (auto& s : logs)
        fout << s << endl;
}