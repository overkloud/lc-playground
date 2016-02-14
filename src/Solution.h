#ifndef __SOLUTION_H_
#define __SOLUTION_H_

#include <tuple>
#include <string>
#include <vector>
#include <map>
#include <cassert>
#include <queue>
#include <cmath>
#include <memory>
#include <set>
#include <stack>
#include <sstream>
#include <functional>
#include <fstream>
#include <cstdio>

using namespace std;

void print(vector<int> &v)
{
    for(auto i : v)
    {
        cout << i << " ";
    }
    cout << endl;
}

void print(vector<vector<int>> &v)
{
    for(auto row : v)
    {
        print(row);
    }
}

template <class T> vector<T> split(const char * str, const char c,  std::function <T(string)> transform)
{
    vector<T> v;
    do
    {
        if (!str || !*str) break;
        const char *begin = str;

        while (*str != c && *str)
            str++;
        v.push_back(transform(string(begin, str)));
    } while (0 != *str++);

    return v;
}

vector<string> split(const char *str, char c = ' ')
{
    function <string(string)> f = [](string &s)
    {
        return std::move(s);
    };
    return split<string>(str, c, f);
}

vector<string> split(const string s, char c = ' ')
{
    return split(s.c_str(), c);
}

vector<int> splitToInts(const char * str, const char c = ' ')
{
    std::function <int(string)> f = [](string s)
    {
        return atoi(s.c_str());
    };
    return split<int>(str, c, f);
}

vector<int> splitToInts(const string s, const char c = ' ')
{
    return splitToInts(s.c_str(), c);
}

vector<int> readInts(istream & in, const char delim = ' ')
{
    string line;
    getline(in, line);
    return splitToInts(line, delim);
}

class solution
{
public:
    virtual void test(){};
    solution(){};
    //private:
    //solution(const BuySellStockII &){};
    //solution & operator = (const BuySellStockII &){};
};



class HRsolution : public solution
{
    virtual void run(istream & in, ostream & out) = 0;
};

#endif