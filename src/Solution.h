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
    virtual ostream & run(istream & in) = 0;
};

#endif