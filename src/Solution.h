#ifndef __SOLUTION_H_
#define __SOLUTION_H_
#ifdef _WIN32
#define NOMINMAX
#include <Windows.h>
#endif 

// c++ basics
#include <string>
#include <cassert>
#include <cmath>
#include <memory>
#include <sstream>
#include <functional>
#include <fstream>
#include <cstdio>
#include <time.h>
#include <iostream>
//algo
#include <random>
#include <algorithm>
// containers
#include <tuple>
#include <queue>
#include <set>
#include <stack>
#include <unordered_map>
#include <list>
#include <forward_list>
#include <vector>
#include <map>

using namespace std;

typedef long long int ll;
typedef unsigned int ui;
typedef unsigned long long int ull;
typedef size_t szt;


#define vt vector
#define pq priority_queue
#define mkp make_pair
typedef vector<int> vint;
typedef vector<ll> vll;

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
        while (*str && *str == c)
            str++;

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
        while (*str && *str==c)
            str++;

    } while (0 != *str);

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

int readInt(istream & in)
{
    string line;
    getline(in, line);
    return atoi(line.c_str());
}

double readDouble(istream & in)
{
    string line;
    getline(in, line);
    return atof(line.c_str());
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

    virtual void run(istream & in, ostream & out) {};
    
    virtual void run()
    {
        ifstream in("a.in");
        run(in, std::cout);
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
    vector<int> randomGen(const int size, const int range, bool file = true)
    {
        vector<int> results(size);
        srand((unsigned int)time(NULL));
        for (int i = 0; i < size; i++)
        {
            results[i] = rand() % range;
        }

        if (file)
        {
            ofstream out("a.random");
            for (auto i : results)
            {
                out << i << " ";
            }
            out.close();
        }
        return results;
    }

    string randomGenWord(const int len)
    {
        string s;
        for (int i = 1; i <= len; i++)
        {
            std::default_random_engine gen;
            std::uniform_int_distribution<int> dist(0, 26);
            char c = (char)(dist(gen) + 'a');
            s.append(1, c);
        }

        return s;
    }

    vector<string> randomGenWords(const int size, const int maxLen)
    {
        vector<string> v;

        vector<int> vv = randomGen(size*maxLen, 101, false);
        int pos = 0;
        ofstream out("a.random");
        
        
        for (int i = 0; i < size; i++)
        {
            for (int j = 1; j < maxLen; j++)
            {
                string s;
                for (int i = 1; i <= j; i++)
                {
                    char c = vv[pos++] % 4 + 'a';
                    s.append(1, c);
                    if (pos == vv.size())
                    {
                        pos = 0;
                        vv = randomGen(size*maxLen, 101, false);
                    }
                }
                //v.push_back(s);
                out << s << endl;
            }
        }
        out.close();


        return v;
    }


    class timer
    {
#ifdef _WIN32
        LARGE_INTEGER StartingTime, EndingTime, ElapsedMicroseconds;
        static LARGE_INTEGER Frequency;
#endif

    public: timer()
        {
#ifdef _WIN32
            QueryPerformanceFrequency(&Frequency);
#endif
        }

        void start()
        {
#ifdef _WIN32
            QueryPerformanceCounter(&StartingTime);
#endif
        }

        double stop()
        {
            // We now have the elapsed number of ticks, along with the
            // number of ticks-per-second. We use these values
            // to convert to the number of elapsed microseconds.
            // To guard against loss-of-precision, we convert
            // to microseconds *before* dividing by ticks-per-second.
#ifdef _WIN32
            QueryPerformanceCounter(&EndingTime);
            ElapsedMicroseconds.QuadPart = EndingTime.QuadPart - StartingTime.QuadPart;
            ElapsedMicroseconds.QuadPart *= 1000000;
            ElapsedMicroseconds.QuadPart /= Frequency.QuadPart;
            return ElapsedMicroseconds.QuadPart / 1000.0;
#else 
            return 0;
#endif
            
        }

        double getTime()
        {
            return stop();
        }

        void clear()
        {
#ifdef _WIN32
            StartingTime.QuadPart = 0;
            EndingTime.QuadPart = 0;
            ElapsedMicroseconds.QuadPart = 0;
#endif
        }

        void reset()
        {
            clear();
            start();
        }

    };

};



#endif
