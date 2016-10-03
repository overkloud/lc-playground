#include "Solution.h"

using namespace std;

class MinSizeSubarraySum: public  solution {

public:


    int minSubArrayLen(int s, vector<int>& n) {
        int result = 0;
        int N = (int)n.size();
        int sum = 0;
        for_each(n.begin(), n.end(), [&sum](int & i) {sum += i; });
        if (sum >= s)
        {
            vint end(N, -1);
            vint sum(N, 0);
            range(N)
            {
                if (i != 0 && end[i - 1] == -1)
                {
                    end[i] = -1;
                    continue;
                }

                if (i== 0 || end[i - 1] < i)
                {
                    int j = i;
                    int subsum = n[j];
                    while (subsum < s && ++j < N)
                    {
                        subsum += n[j];
                    }
                    end[i] = subsum>=s?j:-1;
                    sum[i] = subsum>=s?subsum:0;
                }
                else
                {
                    int subsum = sum[i - 1] - n[i - 1];
                    int j = end[i - 1];
                    while (subsum < s && ++j < N)
                    {
                        subsum += n[j];
                    }
                    end[i] = subsum >= s ? j : -1;
                    sum[i] = subsum >= s ? subsum : 0;
                }
            }

            result = INT_MAX;
            range(N)
            {
                if (end[i] != -1 && sum[i] >= s)
                {
                    result = std::min(result, end[i] - i + 1);
                }
            }
        }
        return result;
    }

    virtual void test()
    {
        vint v1 = { 2,3,1,2,4,3 };
        auto r1 = minSubArrayLen(7, v1);
        assert(r1 == 2);

        auto r2 = minSubArrayLen(0, v1);
        assert(r2 == 1);

        auto r3 = minSubArrayLen(1000, v1);
        assert(r3 == 0);

        vint v4 = { 4 ,4 ,4 ,1 ,2 ,2 ,1, 3 };
        assert(1 == minSubArrayLen(4, v4));

        int testCases = 5;
        range(testCases)
        {
            vint v = testUtil::randomGen(8, 6, false);
            std::this_thread::sleep_for(10ms);
            vint n = testUtil::randomGen(1, 4*6/2, false);
            std::this_thread::sleep_for(1s);
            auto r = minSubArrayLen(n[0], v);
            vector2Stream(cout, v);
            vector2Stream(cout, n);
            cout << "result: " << r << endl;
        }
    }
};
