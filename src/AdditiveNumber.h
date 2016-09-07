#include "Solution.h"

using namespace std;

class AdditiveNumber: public  solution {

public:

    bool calc(string s)
    {
        int n = s.size();

        std::function <ll(int i, int j)> get = [&s](int i, int j)
        {

            //if (i != j && s[i] == '0') return -1L;

            if (j >= i)
            {
                return atol(s.substr(i, j - i + 1).c_str());
            }
            return -1l;
        };

        for (int i = 0; i < n - 2; i++)
        {
            if (i != 0 && s[0] == '0') break;
            ll i1 = get(0, i);
            for (int j = i + 1; j < n - 1; j++)
            {
                if (j - i > 1 && s[i+1] == '0') break;
                ll i2 = get(i + 1, j);

                ll t1 = i1;
                ll t2 = i2;
                bool match = false;
                int first = i;
                int second = j;


                int k = second + 1;
                while (k < n)
                {
                    if (k - second > 1 && s[second+1] == '0') break;
                    ll i3 = get(second + 1, k);

                    if (i3 > t1 + t2) break;
                    else if (i3 < t1 + t2)
                    {
                        k++;
                    }
                    else
                    {
                        match = true;
                        first = second;
                        second = k;
                        t1 = t2;
                        t2 = i3;
                        k++;
                    }
                }

                if (k == n && match) return true;

            }
        }

        return false;
    }

    virtual void test()
    {
        assert(calc("112358"));
        assert(calc("199100199"));
        assert(!calc("1203"));
        assert(!calc("0235813"));
    }
};
