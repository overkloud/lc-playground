#include "Solution.h"

using namespace std;

class SumMinInterval: public  solution {

public:

    // so that M[i][j] = the min of given interal v[i]...[j] both inclusive

    void calcIntervals(vector<int> & v, vector<vector<int>> & M, const int interval)
    {
        if (0 == interval)
        {
            for (int i = 0; i < v.size(); i++)
            {
                M[i][i] = v[i];
            }
        }
        else
        {
            for (int i = 0; i < v.size() - interval; i++)
            {
                M[i][i + interval] = min(M[i][i + interval - 1], v[i + interval]);
            }
        }
    }

    void calcIntervals(vector<int> & v, vector<vector<int>> & M)
    {
        szt n = v.size();
        for (int i = 0; i < n; i++)
        {
            M.push_back(vector<int>(n));
        }

        for (int i = 0; i <= n; i++)
        {
            calcIntervals(v, M, i);
        }
    }

    

    long long calcMins(vector<int> & v)
    {
        vector<vector<int>> M;
        std::function <int(int, int)> f = [&M](int a, int b)
        {
            return M[a][b];
        };

        szt N = v.size();

        calcIntervals(v, M);

        int ans = 0;
        for (int a = 0; a < N; a++)
        {
            for (int b = a; b < N; b++)
            {
                for (int c = b + 1; c < N; c++)
                {
                    for (int d = c; d < N; d++)
                    {
                        ans += min(f(a, b), f(c, d));
                    }
                }
            }
        }

        return ans;
    }

    void calc(vector<int> & M)
    {
        long long ans = calcMins(M);;
        cout << ans % ((int)pow(10, 9) + 7) << endl;
    }

    void run(istream & in)
    {
        string line;
        getline(in, line);
        int N = atoi(line.c_str());
        vector<int> v = readInts(in, ' ', N);
        calc(v);
    }

    virtual void test()
    {
        ifstream in("a.in");
        run(in);
        //testUtil::randomGen(10000, 1000000);
    }
};
