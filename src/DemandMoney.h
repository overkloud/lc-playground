#include "Solution.h"

using namespace std;

class DemandMoney: public  solution {

public:

/*
unfinished https://www.hackerrank.com/contests/w21/challenges/borrowing-money
    */

    void setIntBit(ll & it, int n, int m, int b)
    {
        int nn = m - n - 1;
        int x = it;
        x = x >> nn;
        if (x & 0x01 == b) return;

        int mask = 0x01;
        mask = mask << nn;
        it = it ^ mask;
    }

    int getIntBit(ll it, int n, int m) {
        int bit = it;
        int nn = m - n - 1;
        for (int i = 0; i < nn; i++) { bit = bit >> 1; }
        int out = bit & 0x01;
        return out;
    }

    void calc(vector<vint> &M, int n, const vint &L, set<ll>& S)
    {
        if (n == 0)
        {
            ll s1 = 0;
            setIntBit(s1, 0, L.size(), 1);
            S.insert(s1);
            return;
        }
        calc(M, n - 1, L, S);
        set<ll> newS;
        int newConnectedS = 0;
        vint connected;
        fori(L.size())
        {
                if (M[i][n])
                {
                    connected.push_back(i);
                }
        }
        for (auto s1 : S)
        {
            bool hasConnected = false;
            for (auto c : connected)
            {
                if (getIntBit(s1, c, L.size()))
                {
                    hasConnected = true;
                    break;
                }
            }

            if (hasConnected) {
                newConnectedS++;
                newS.insert(s1);
            }
            else
            {
                setIntBit(s1, n, L.size(), 1);
                newS.insert(s1);
            }
        }
        if (newConnectedS == S.size())
        {
            ll s1 = 0;
            setIntBit(s1, n, L.size(), 1);
            newS.insert(s1);
        }
        S = newS;
    }

    ll calc2(vector<vint> &M, int n, const vint &L, set<ll>& S)
    {
        if (n == 0)
        {
            /*vint s1(L.size(), 0);
            s1[n] = 1;*/
            ll s1 = 0;
            setIntBit(s1, 0, L.size(), 1);
            S.insert(s1);
            return L[n];
        }

        ll r1 = calc2(M, n - 1, L, S);
        ll localMax = r1;
        set<ll> newS;
        for (auto s1 : S) {
            ll sum = 0;
            vint connected;
            fori(L.size())
            {
                if (getIntBit(s1, i, L.size())) {
                    if (M[i][n])
                    {
                        sum += L[i];
                        connected.push_back(i);
                    }
                }
            }

            ll newsum = r1 - sum + L[n];
            ll offset = s1;
            ll notInS = (ll)(pow(2,L.size())-1)^offset;
            vint addon;
            fori(L.size())
            {
                //int p = notInS | (notInS >> 1);
                ll x = (notInS) & 0x01;
                int p = L.size() - i - 1;
                if (x && M[p][n] == 0 && p < n)
                {
                    newsum += L[p];
                    addon.push_back(p);
                }
                notInS = notInS >> 1;
            }

            if (newsum >= localMax)
            {
                localMax = newsum;
                for (auto c1 : connected)
                {
                    //s1[c1] = 0;
                    setIntBit(s1, c1, L.size(), 0);
                }
                for (auto i : addon)
                {
                    //s1[i] = 1;
                    setIntBit(s1, i, L.size(), 1);
                }
                //s1[n] = 1;
                setIntBit(s1, n, L.size(), 1);
                if (newsum > localMax) newS.clear();
                newS.insert(s1);
            }
        }

        if (r1 == localMax)
        {
            for (auto i : S)
            {
                newS.insert(i);
            }
        }

        S = newS;

        return localMax;
    }

    ll calc(vector<vint> & v, vint L, int n)
    {
        vector<vint> M;

        for (int i = 0; i < n; i++)
        {
            vint vv(n, 0);
            M.push_back(vv);
        }


        for (auto v1 : v)
        {
            auto i = v1[0] - 1;
            auto j = v1[1] - 1;
            M[i][j] = 1;
            M[j][i] = 1;
        }

        set<ll> s;

        calc(M, n - 1, L, s);
        ll result = 0;
        ll count = 0;

        for (auto s1 : s)
        {
            vint v;
            ll sum = 0;
            fori(L.size())
            {
                if (getIntBit(s1, i, L.size()))
                {
                    sum += L[i];
                }
            }

            if (sum > result)
            {
                count = 1; 
                result = sum;
            }
            else if (sum == result)
            {
                count++;
            }
        }

        cout << result << " " << count << endl;
        return 0;
    }

    void run(istream & in)
    {
        vint v1 = readInts(in, ' ', 2);
        int N = v1[0];
        int M = v1[1];
        vint L = readInts(in, ' ', N);
        vector<vint> vv;
        fori(M)
        {
            vint v = readInts(in, ' ', 2);
            vv.push_back(v);
        }

        ll result = calc(vv, L, N);
    }


    virtual void test()
    {
        ifstream in("a.in");
        run(in);
    }
};
