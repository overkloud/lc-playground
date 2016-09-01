#include "Solution.h"

using namespace std;

class NumberSolitaire: public  solution {

public:

    /*
    In a given array, find the subset of maximal sum in which the distance between consecutive elements is at most 6.
    https://codility.com/programmers/task/number_solitaire/
    */
    int solution(vector<int> &A) {
        if (A.size() == 0) return 0;
        // write your code in C++11 (g++ 4.8.2)
        vector<int> S(A.size(), INT_MIN);
        S[0] = A[0];
        for (int i = 1; i < A.size(); i++)
        {
            int prevMax = INT_MIN;
            if (i - 6 < 0) 
            {
                for (int j = 0; j < i; j++)
                    prevMax = std::max(prevMax, S[j]);
            }
            else
            {
                for (int j = 1; j <= 6; j++)
                    prevMax = std::max(prevMax, S[i - j]);
            }
            S[i] = prevMax + A[i];
        }

        return S[A.size() - 1];
    }

    virtual void test()
    {
        vector<int> A = { 1, -2, 0, 9, -1, -10, -10, -2, -10, -12, -20 };
        int i = solution(A);
    }
};
