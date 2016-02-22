#include "Solution.h"

using namespace std;

class MaxSumModuleSubarray: public  solution {

public:

    /*
    https://www.hackerrank.com/challenges/maximise-sum
    You are given an array of size N and another integer M. Your target is to find the maximum value of sum of subarray modulo M.

    Subarray is a continuous subset of array elements.

    Note that we need to find the maximum value of (Sum of Subarray)%M , where there are N¡Á(N+1)/2N¡Á(N+1)/2 possible subarrays.

    For a given array A[] of size N, subarray is a contiguous segment from i to j where 0¡Üi¡Üj¡ÜN
    */
    typedef long long int ll;
    struct P
    {
        ll pos;
        ll val;


        P(ll p, ll v)
        {
            pos = p;
            val = v;
        }

        bool operator < (const P& r) const
        {
            return this->val < r.val;
        }
    };


    ll findMax2(vector<ll> & v, const ll M)
    {
        vector<ll>  x;
        ll max = 0;
        for (ll i = 0; i < v.size(); i++)
        {
            if (0 == i)
            {
                ll a = v[i] % M;
                x.push_back(a);
            }
            else
            {
                ll a = (x[i - 1] + v[i]) % M;
                x.push_back(a);
            }
        }

        for (ll i = 0; i < v.size(); i++)
        {
            max = std::max(max, x[i]);
            if (v.size() - 1 == max) return max;

            for (ll j = 0; j < i; j++)
            {
                ll a = (x[i] - x[j] + M) % M;
                max = std::max(a, max);
            }
        }

        return max;
    }

    ll findMax(vector<ll> & v, const ll M)
    {
        vector<ll>  x;
        set<P> s;

        for (ll i = 0; i < v.size(); i++)
        {
            if (0 == i)
            {
                ll a = v[i] % M;
                x.push_back(a);
                s.insert( P(i, a));
            }
            else
            {
                ll a = (x[i - 1] + v[i]) % M;
                x.push_back(a);
                s.insert( P(i, a));
            }
        }

        ll max = 0;
        for (ll i = 0; i < x.size(); i++)
        {
            if (x[i] == M - 1) return M - 1;

            auto it = s.lower_bound(P(0,x[i] + 1));

            if (it == s.end() || it->pos > i)
            {
                max = std::max(x[i], max);
            }
            else
            {
                max = std::max(std::max(x[i], x[i] + M - it->val), max);
            }
        }


        return max;
    }


    void run(istream &in)
    {
        string line; 
        getline(in, line);
        ll t, n, m;
        t = atoll(line.c_str());

        for (ll i = 0; i < t; i++)
        {
            vector<ll> a = readLLInts(in, ' ', 2);
            n = a[0];
            m = a[1];
            vector<ll> v = readLLInts(in, ' ', n);
            cout << findMax(v, m) << endl;
        }
        //cout << findMax2(v, m) << endl;
    }

    virtual void test()
    {
        ifstream in("a.in");
        run(in);
    }
};
