#include "Solution.h"

using namespace std;

class TwoEqualSubArrays: public  solution {

public:

    typedef long long int ll;

    bool run(vector<int> &v)
    {
        ll sum = 0;

        vector<ll> x;

        for (int i = 0; i < v.size(); i++)
        {
            sum += v[i];
            if (i == 0) x.push_back(v[i]);
            else
            {
                x.push_back(v[i] + x[i - 1]);
            }
        }

        for (int i = 0; i < x.size(); i++)
        {
            if (0 == i)
            {
                if (sum - x[0] == 0)
                    return true;
            }
            else
            {
                if (x[i] + x[i - 1] == sum)
                    return true;
            }
        }

        return false;
    }

    void run(istream & in)
    {
        int t;
        string line;
        getline(in, line);
        t = atoi(line.c_str());
        for (int i = 0; i < t; i++)
        {
            int n;
            getline(in, line);
            n = atoi(line.c_str());
            vector<int> v = readInts(in, ' ', n);
            string s = run(v) ? "YES" : "NO";
            cout << s << endl;
        }
        
    }

    virtual void test()
    {
        ifstream in("a.in");
        run(in);
    }
};
