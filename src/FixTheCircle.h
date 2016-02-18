#include "Solution.h"

using namespace std;

class FixTheCircle: public  solution {

public:



    int fix(vector<int> &v)
    {
        vector<vector<int>> circles= {
            {0, 1, 5},
            {0, 1, 2, 3},
            {0, 3, 4}
        };

        vector<int> sums;
        int min = 0;
        for (auto c : circles)
        {
            int sum = 0;
            for (auto i : c)
            {
                sum += v[i];
            }
            if (min > sum) min = sum;
        }

        if (min < 0) return -min;

        return 0;
    }


    void run(istream & in)
    {
        vector <int> v= readInts(in);
        cout << fix(v) << endl;
    }

    virtual void test()
    {
        ifstream in("a.in");
        vector<int> v = testUtil::randomGen(7, 10);
        vector<int> v3;
        for (int i = 0; i < 6; i++)
        {
            v3.push_back(v[i] - v[6]);
        }
        print(v3);
        //cout << fix(v3) << endl;
        run(in);
    }
};
