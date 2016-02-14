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


vector<string> split(const char *str, char c = ' ')
{
    vector<string> result;

    do
    {
        const char *begin = str;

        while (*str != c && *str)
            str++;

        result.push_back(string(begin, str));
    } while (0 != *str++);

    return result;
}

vector<string> split(const string s, char c = ' ')
{
    return split(s.c_str(), c);
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