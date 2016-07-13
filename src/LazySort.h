#include "Solution.h"
#include <type_traits>
using namespace std;

class LazySort: public  solution {

    /*
    incorrect  https://www.hackerrank.com/contests/w21/challenges/lazy-sorting
    */

public:


    ll approx(ll n, ll m)
    {
        ll i = 1;
        double result = 0;
        //double epsilon = 10e-9;
        double epsilon = std::numeric_limits<double>::epsilon();
        
        double p = n * 1.0 / m;
        double left = 1.0;
        while (true)
        {
            if (i == 1)
            {
                i++;
                result = 1 * p;
                left = 1 - p;
            }
            else
            {
                double r1 = (i*(left)*p);
                left -= left*p;
                if (left < epsilon || i <= 0) break;
                i++;
                result += r1;
            }
        }

        if (result - floor(result) >= 0.5) return (ll)ceil(result);
        return (ll)floor(result);
    }

    ll fact(int i)
    {
        if (i == 0 || i == 1) return 1L;
        else return i*fact(i - 1);
    }

    void run(istream & in)
    {
        int P;
        P = readInt(in);
        vint v = readInts(in, ' ', P);
        ll m = fact(v.size());


        map<int, int> map;
        for (auto i : v)
        {
            if (map.find(i) == map.end()) map.insert(mkp(i, 1));
            else {
                map[i]++;
            }
        }

        ll n = 1;
        for (auto i : map)
        {
            n = n*fact(i.second);
        }
        // calc perm of v
        cout << approx(n, m) << endl;
    }

    void test()
    {
        ifstream in("a.in");
        run(in);
    }

};
