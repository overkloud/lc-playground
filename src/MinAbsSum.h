#include "Solution.h"

using namespace std;

class MinAbsSum: public  solution {

public:

    /*
    Given array of integers, find the lowest absolute sum of elements.
    https://codility.com/programmers/task/min_abs_sum/
    */

    int slow_solution(vector<int> &A) {
        

        int N = A.size();
        int S = 0;
        for (int &i : A)
        {
            i = std::abs(i);
            S += i;
        }

        vint dp(S + 1, 0);
        dp[0] = 1;
        for (auto i : A)
        {
            // the order here is important, has to be reverse so each element is used only once
            for (int j = S; j >= 0; j--)
            {
                if (dp[j] == 1 && j + i <= S)
                {
                    dp[j + i] = 1;
                }
            }
        }

        int result = INT_MAX;
        for (int i = 0; i <= (int)std::ceil(S/2.0); i++)
        {
            if (dp[i] == 1)
                result = std::min(result, std::abs((S - 2*i)));
        }

        return result;
    }

    int solution(vector<int> & A)
    {
        if (A.size() == 0) return 0;

        int max = INT_MIN;
        int S = 0;
        for (int & i : A)
        {
            i = abs(i);
            S += i;
            max = std::max(i, max);
        }

        vector<int> count(max + 1, 0);
        for (auto i : A)
        {
            count[i]++;
        }

        vint dp(S + 1, -1);
        dp[0] = 0;

        for (int i = 1; i <= max; i++)
        {
            if (count[i] > 0)
            {
                for (int j = 0; j <= S; j++)
                {
                    if (dp[j] >= 0) dp[j] = count[i];
                    else if (j - i >= 0 && dp[j - i] > 0) dp[j] = dp[j - i] - 1;
                }
            }
        }

        int result = INT_MAX;
        for (int i = 0; i <= (int)std::ceil(S / 2.0); i++)
        {
            if (dp[i] >= 0)
                result = std::min(result, std::abs((S - 2 * i)));
        }

        return result;
    }

    virtual void test()
    {
        vint A = { 1,5,2,-2};
        int i = solution(A);
        int j = slow_solution(A);

        vint B = {1};
        i = solution(B);
        j = slow_solution(B);

        A = testUtil::randomGen(1000, 100, false);
        i = solution(A);
        j = slow_solution(A);

    }
};
