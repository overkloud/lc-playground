#include "Solution.h"

using namespace std;

class SuperPow: public  solution {

public:

    int simplePow(ll a, ll b, int mod)
    {
        int result = 1;
        for (int i = 0; i < b; i++)
        {
            result = (result * a)%mod;
        }
        return result%mod;
    }

    struct node
    {
        map<ll, int>* m;
        ll start;
        ll k;
        
        node(map<ll, int> *m, ll start, ll k) :
            m(m), start(start), k(k) {};
    };
    map< pair<int, int>, node> M;
    // calc a^(bi*base^pow)%mod
    int calc(ll a, int bi, int base, int pow, int mod)
    {
        int result = 1;

        if (bi == 0 || base == 0 || a == 0) return 1%mod;

        if (bi == 1 && base == 1 && pow <= 1)
        {
            return a % mod;
        }

        a = a % mod;
        
        map<ll, int>* m;
        ll k = -1;
        ll start = -1;
        if (M.find(mkp(a, mod)) != M.end())
        {
            auto it = M.find(mkp(a, mod));
            m = (it->second.m);
            k = (it->second.k);
            start = (it->second.start);
        }
        else
        {
            map<int, ll> s;
            m = new map<ll, int>();
            for (ll i = 0; k == -1; i++)
            {
                auto x = simplePow(a, i, mod);
                auto it = s.find(x);
                if (it != s.end())
                {
                    k = i - it->second;
                    start = it->second;
                }
                else
                {
                    m->emplace(i, x);
                    s.emplace(x, i);
                }
            }
            node n(m, start, k);
            M.emplace(mkp(mkp(a, mod), n));
        }

        auto reduce_pow = calc(base, 1, pow, 1, (int)k);
        auto index = reduce_pow;
        if (start != 0 && index == 0)
        {
            index += (int) k;
        }

        result = simplePow((*m)[index], bi, mod);

        return result;
    }


    const int m = 1337;
    int superPow(int a, vector<int>& b) {

        szt n = b.size();

        int result = 1;
        if (n == 0) return 0;

        fori(n)
        {
            int x = calc(a, b[i], 10, (int)n - 1 - i, m);
            result = (result * x) % m;
        }


        return result;
    }

    virtual void test()
    {
        int a = 2;
        vint b = {0,1,0,1,0,0};
        auto m = superPow(a, b);
        assert(m == 753);


        int a2 = 2;
        vint b2 = { 0 };
        auto m2 = superPow(a2, b2);
        assert(m2 == 1);

        int a7 = 2;
        vint b7 = { 0,0};
        auto m7 = superPow(a7, b7);
        assert(m7 == 1);

        int a3 = 2;
        vint b3 = { 9, 7};
        auto m3 = superPow(a3, b3);
        assert(m3 == 1150);

        int a6 = 1357;
        vint b6 = { 1,2,3,4,5,6,7,8,9,1,2,3,4,1 };
        auto m6 = superPow(a6, b6);
        assert(m6 == 1266);

        int a5 = 135;
        vint b5 = { 1,1 };
        auto m5 = superPow(a5, b5);
        assert(m5 == 998);

        int a4 = 2;
        vint b4 = { 1 };
        auto m4 = superPow(a4, b4);
        assert(m4 == 2);

        int a8 = 1;
        vint b8 = { 8,8,8 };
        auto m8 = superPow(a8, b8);
        assert(m8 == 1);

        int a9 = 721;
        vint b9 = { 1,0,0,0 };
        auto m9 = superPow(a9, b9);
        assert(m9 == 1176);

        M.clear();
        testUtil::timer t;
        t.start();
        int a10 = 209253;
        vint b10 = { 3,6,4,3,0,7,9,2,9,7,8,7,7,0,3,8,6,0,0,8,0,8,3,4,4,4,9,9,6,7,3,3,6,7,8,6,4,8,8,3,7,9,2,4,1,5,4,9,7,4,8,8,4,3,4,8,9,6,0,6,3,3,1,1,2,1,8,8,1,8,3,8,9,5,4,0,3,9,0,0,5,0,0,0,5,5,0,7,1,0,5,6,5,6,8,9,9,8,7,1,6,0,9,6,8,6,8,1,5,0,3,0,0,4,0,8,1,1,5,2,3,0,0,9,8,8,8,7,6,8,8,5,8,0,3,8,6,3,1,3,4,5,3,6,1,6,4,2,9,9,6,2,1,6,1,9,7,2,7,5,0,7,0,0,9,5,9,7,9,2,0,3,9,4,1,0,0,6,4,9,7,2,3,9,9,5,8,8,9,7,3,9,7,4,9,6,1,0,6,0,3,6,5,4,2,7,5,2,3,1,3,0,4,9,1,5,6,0,3,5,9,6,4,6,2,5,5,4,8,1,4,3,7,2,7,0,9,4,4,4,6,0,6,2,9,8,7,5,0,0,0,9,8,6,6,1,3,1,5,3,2,1,6,1,3,6,1,4,2,6,0,8,8,9,2,7,7,9,4,7,1,4,8,0,2,4,3,5,7,0,1,9,1,7,1,7,5,4,3,8,2,6,8,0,5,1,9,2,2,3,1,6,9,9,8,1,6,1,9,3,1,0,5,4,9,8,3,5,4,7,5,7,3,3,9,8,6,9,2,9,2,5,5,2,6,3,5,2,6,6,8,7,6,5,3,8,5,7,5,9,6,0,8,9,5,8,9,2,7,3,3,1,0,0,5,6,5,3,1,1,9,1,0,6,6,3,6,3,2,1,2,8,1,1,9,8,1,0,2,0,3,5,1,3,7,9,2,2,2,3,3,1,4,3,9,2,9,5,5,1,6,9,0,9,2,9,0,3,0,2,5,5,0,9,1,7,8,3,0,2,8,3,5,4,9,7,6,8,2,3,9,1,4,1,2,9,3,2,4,5,5,0,0,7,9,3,4,9,6,4,1,6,0,8,0,9,5,8,9,0,3,0,1,8,2,5,9,7,0,3,2,7,3,2,4,4,8,8,3,4,3,6,3,3,5,3,4,0,2,5,0,7,5,3,5,9,9,6,6,1,0,8,8,5,3,2,0,1,0,3,7,5,2,0,0,7,4,6,7,8,1,0,5,7,5,3,6,4,9,5,7,1,3,5,7,6,7,9,9,0,4,7,5,6,9,6,3,5,2,3,5,4,5,1,3,0,6,1,7,7,6,4,1,0,0,8,8,7,9,8,7,3,7,5,2,8,3,5,4,5,0,9,1,7,2,6,8,0,8,7,8,4,1,9,6,3,9,5,3,8,5,2,3,4,7,5,2,0,3,6,8,5,8,9,3,0,6,3,1,6,0,1,0,1,2,7,5,1,4,8,1,1,2,6,7,0,2,9,0,7,8,0,2,8,2,7,8,0,0,1,6,0,2,8,4,4,7,1,7,1,1,0,4,3,7,1,3,1,3,6,8,1,8,0,9,0,8,9,0,0,3,6,1,5,5,7,2,2,8,1,6,9,4,0,2,1,4,8,2,7,6,2,0,4,2,1,5,2,0,7,3,3,4,6,1,1,3,5,5,1,8,1,2,2,4,6,5,0,6,7,7,2,9,9,9,4,0,6,8,0,3,3,6,9,1,9,2,4,4,8,7,4,1,1,7,7,8,2,7,4,2,6,9,3,5,0,9,7,6,0,8,1,3,6,1,5,5,5,1,1,5,1,5,7,2,4,6,2,9,6,9,3,4,8,8,2,8,8,9,6,8,7,7,3,5,0,8,0,6,2,3,1,3,1,0,7,5,7,0,6,5,9,9,9,9,8,1,9,8,1,5,6,0,4,1,6,5,2,8,3,4,2,4,9,3,7,6,0,4,8,7,1,9,8,0,8,6,2,9,6,5,4,2,5,1,6,3,6,8,2,9,4,6,5,3,9,2,1,1,8,0,8,9,9,7,2,0,5,6,9,2,1,6,6,8,7,2,2,5,2,6,6,6,2,1,9,3,6,3,4,6,3,5,6,4,2,0,6,9,6,8,1,7,4,0,5,1,4,9,6,7,5,4,3,7,5,5,2,3,8,7,0,3,2,8,9,6,8,6,5,4,4,9,3,0,9,0,1,3,0,9,0,5,3,6,5,0,1,7,6,9,6,6,2,8,6,1,4,6,9,2 };
        auto m10 = superPow(a10, b10);
        assert(m10);
        cout << "time spend " << t.stop() << endl;


        M.clear();
        t.reset();
        int a11 = 4499194;
        vint b11 = { 2,0,5,1,0,6,7,5,4,5,4,9,7,6,7,8,4,4,9,6,9,8,0,3,4,5,6,2,0,6,6,8,7,1,9,9,9,9,6,5,4,1,4,3,9,3,1,3,9,3,1,9,1,3,4,7,8,1,0,1,9,6,9,8,0,8,0,1,7,6,7,3,9,3,6,8,7,0,3,6,3,6,7,6,2,2,4,0,5,4,1,6,2,0,5,2,1,7,4,0,3,3,6,5,6,4,5,3,4,9,2,9,7,1,6,9,3,0,2,0,6,3,7,8,6,4,3,9,1,9,1,4,2,7,1,8,2,7,4,6,8,8,8,5,9,4,7,5,6,9,5,2,4,2,2,0,6,5,1,7,6,3,4,8,0,5,9,4,4,5,3,2,3,1,8,4,5,5,9,3,4,5,7,8,9,9,1,6,7,4,5,3,7,9,4,0,7,3,4,1,0,7,6,3,8,4,7,5,1,7,0,7,4,7,7,3,9,0,9,6,5,7,1,4,8,7,4,5,0,9,9,0,8,5,5,9,1,5,6,2,4,7,1,8,6,8,1,5,9,3,3,6,2,7,0,0,4,5,8,7,6,7,9,4,4,5,5,5,0,2,9,4,1,0,4,7,0,7,5,1,0,0,7,2,7,8,5,4,3,3,1,1,0,0,7,6,7,3,3,9,7,2,5,0,4,9,7,4,7,4,8,9,5,5,4,4,3,9,8,8,2,9,1,4,2,9,2,9,4,5,1,1,9,6,1,3,8,0,9,7,7,7,6,2,5,2,8,8,3,7,9,7,8,0,1,0,9,3,2,3,0,3,6,9,9,9,4,9,2,4,6,9,3,3,3,8,7,1,9,1,0,8,8,9,0,2,9,0,7,1,5,8,6,4,9,8,5,4,7,9,0,4,8,3,9,3,4,6,7,5,9,7,5,8,6,5,2,8,7,1,9,5,9,8,9,1,6,6,5,3,6,5,7,6,0,6,0,6,5,7,1,4,6,6,4,3,2,8,1,9,0,2,4,1,0,5,2,8,4,7,2,0,4,1,6,5,0,8,3,5,7,5,1,4,1,8,9,5,6,2,5,8,4,1,0,7,9,2,7,3,2,9,5,6,1,3,3,3,2,7,8,1,4,1,7,5,1,6,1,0,8,8,8,5,1,8,4,2,3,1,7,5,3,2,3,6,6,9,9,0,6,9,3,0,2,1,7,4,9,0,4,0,0,4,7,4,3,1,6,8,4,4,5,9,8,8,5,6,7,6,8,5,7,2,7,0,3,7,6,4,9,2,4,0,6,1,4,9,4,2,9,9,8,4,0,7,3,8,5,2,4,4,0,4,6,9,4,1,6,2,5,6,4,0,8,0,1,4,2,6,6,1,7,7,6,9,6,1,7,1,5,4,5,5,8,1,5,4,2,3,6,0,9,2,0,9,2,3,3,6,1,0,8,0,9,6,0,5,9,9,6,4,3,2,2,3,5,9,7,0,2,5,0,4,7,2,3,2,5,7,8,9,9,8,9,8,4,1,5,5,1,1,2,6,3,6,0,9,5,9,1,9,5,1,5,4,3,1,8,0,0,7,1,9,5,3,9,2,4,4,9,7,7,1,4,1,7,6,2,4,5,3,4,2,6,1,7,1,2,7,3,2,4,5,3,2,8,4,6,4,8,5,4,6,7,8,9,6,4,3,1,1,8,7,4,4,8,3,5,1,0,8,5,5,5,9,9,5,3,5,0,4,0,4,2,7,4,3,4,0,6,7,1,4,4,5,0,2,8,5,3,1,5,9,8,1,0,7,8,3,2,8,9,2,4,1,2,8,6,8,0,2,5,2,8,9,7,8,3,8,5,9,1,3,0,9,6,0,6,4,5,0,5,7,4,9,0,8,0,7,6,0,1,3,2,0,4,2,0,8,2,8,9,3,1,9,4,9,9,2,3,6,2,8,3,6,0,4,7,0,1,3,2,2,9,5,4,5,9,5,3,3,5,4,8,6,3,2,5,4,4,0,1,6,9,6,4,1,0,1,1,3,7,5,8,8,2,2,3,1,9,9,6,4,3,4,2,9,6,9,3,0,0,4,8,1,3,5,2,3,8,5,9,7,0,7,5,3,1,1,6,1,0,3,7,5,7,2,4,4,1,8,6,1,4,7,2,7,2,6,3,2,1,4,0,4,1,7,7,4,8,3,7,0,8,5,8,6,7,2,2,0,2,8,2,9,7,6,8,9,3,3,4,6,7,4,0,0,1,9,5 };
        auto m11 = superPow(a11, b11);
        assert(m11 == 70);
        cout << "time spend " << t.stop() << endl;
        
    }
};
