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
#include <time.h>
#include <iostream>

using namespace std;

typedef long long int ll;
typedef unsigned int ui;
typedef unsigned long long int ull;
typedef size_t szt;

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

template <class T> vector<T> split(const char * str, const char c,  std::function <T(string)> transform, int size = 0)
{
    vector<T> v(size);
    int count = 0;
    do
    {
        if (!str || !*str) break;
        const char *begin = str;

        while (*str != c && *str)
            str++;
        if (0 == size)
        {
            v.push_back(transform(string(begin, str)));
        }
        else
        {
            if (count == size) break;
            v[count++] = transform(string(begin, str));
        }

    } while (0 != *str++);

    return v;
}

vector<string> split(const char *str, char c = ' ')
{
    function <string(string)> f = [](string &&s)
    {
        return std::move(s);
    };
    return split<string>(str, c, f);
}

vector<string> split(const string s, char c = ' ')
{
    return split(s.c_str(), c);
}

vector<int> splitToInts(const char * str, const char c = ' ', const int size = 0)
{
    std::function <int(string)> f = [](string s)
    {
        return atoi(s.c_str());
    };
    return split<int>(str, c, f, size);
}

vector<int> splitToInts(const string s, const char c = ' ', const int size = 0)
{
    return splitToInts(s.c_str(), c, size);
}

vector<long long int> readLLInts(istream & in, const char delim = ' ', const int size = 0)
{
    string line;
    getline(in, line);
    std::function <long long int(string)> f = [](string s)
    {
        return atoll(s.c_str());
    };
    return split<long long int>(line.c_str(), delim, f, size);
}

vector<int> readInts(istream & in, const char delim = ' ', const int size = 0)
{
    string line;
    getline(in, line);
    return splitToInts(line, delim, size);
}

template <class T>
void initArray(T *array, const int size, function<T()> initFunc)
{
    for (int i = 0; i < size; i++)
    {
        array[i] = initFunc();
    }
}


class solution
{
public:
    virtual void run(istream & in){};
    
    virtual void run()
    {
        ifstream in("a.in");
        run(in);
    }
    virtual void test(){ run();  };
    solution(){};
    
};



class HRsolution : public solution
{
    virtual void run(istream & in, ostream & out) = 0;
};


namespace testUtil
{
    vector<int> randomGen(const int size, const int range)
    {
        vector<int> results(size);
        srand((unsigned int)time(NULL));
        for (int i = 0; i < size; i++)
        {
            results[i] = rand() % range;
        }

        ofstream out("a.random");
        for (auto i : results)
        {
            out << i << " ";
        }
        out.close();
        return results;
    }

};



#endif
