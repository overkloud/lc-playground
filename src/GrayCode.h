#include "Solution.h"

using namespace std;

/**
The gray code is a binary numeral system where two successive values differ in only one bit.

Given a non-negative integer n representing the total number of bits in the code, print the sequence of gray code. A gray code sequence must begin with 0.

For example, given n = 2, return [0,1,3,2]. Its gray code sequence is:
***/

class GrayCode: public  solution {

public:
    vector<int> grayCode(int n) {
        if (0 == n)
            return vector<int>{0};
        if (1 == n)
            return vector<int>{0, 1};
        if (2 == n)
            return vector<int>{0, 1, 3, 2};

        const vector<int> & n_1 = grayCode(n - 1);

        vector<int> ret(pow(2, n));
        int k = 0;
        for (auto a : n_1)
        {
            int b = a << 1;
            ret[k++] = b;
        }
        for (int i = n_1.size() - 1; i >= 0; i--)
        {
            int b = n_1[i] << 1;
            b = b | 1;
            ret[k++] = b;
        }

        return ret;
    }

    virtual void test()
    {
        const vector<int> test1 = grayCode(4);
    }
};
