#include "Solution.h"

/*
You are climbing a stair case. It takes n steps to reach to the top.

Each time you can either climb 1 or 2 steps. In how many distinct ways can you climb to the top?
*/
using namespace std;
class ClimbStairs : public solution
{
public:
    int climbStairs(int n) {
        if (n == 0) return 0;

        if (n == 1)
            return 1;
        else if (n == 2)
            return 2;
        /*
        else
        {
            return climbStairs(n - 1) + climbStairs(n - 2);
        }*/


        vector <int> A;
        A.reserve(n);
        A.push_back(1);
        A.push_back(2);
        for (int i = 2; i < n; i++)
        {
            A.push_back(A[i - 1] + A[i - 2]);
        }

        return A[n - 1];
    }

    void test()
    {
        assert(0 == climbStairs(0));
        assert(1 == climbStairs(1));
        assert(2 == climbStairs(2));
        assert(3 == climbStairs(3));
        assert(5 == climbStairs(4));
        assert(8 == climbStairs(5));
        std::cout << "finished climb stairs" << endl;
    }
};

