#include "Solution.h"


//Reverse digits of an integer.
//
//Example1: x = 123, return 321
//Example2 : x = -123, return -321
class ReverseInteger : public  solution {
public:
    int reverse(int x) {
        using namespace std;

        if (x == 0) return 0;

        
        bool negative = (x < 0);
        vector<int> V;

        if (negative) x = x * -1;

        int s = x;
        while (s != 0)
        {
            V.push_back(s % 10);
            s = s / 10;
        }

        int ret = 0;
        for (unsigned int i = 0; i < V.size(); i++)
        {
            const size_t power = V.size() - i - 1;
            ret = ret + (int)(V[i] * pow(10, power));
        }

        if (negative) ret = ret * -1;

        return ret;
    }


    void test()
    {
        assert(1 == reverse(1));
        assert(1 == reverse(100));
        assert(-1 == reverse(-100));
        assert(-123 == reverse(-321));
        assert(-123 == reverse(-3210));
    }
};
