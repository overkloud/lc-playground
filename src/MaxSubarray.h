#include "Solution.h"

using namespace std;

class MaxSubarray: public  solution {

public:



    ll calcSubArray(const vint & v)
    {
        return 0;
    }

    ll calcPosSum(const vint & v)
    {
        ll sum = 0l;
        for (auto i : v)
        {
            if (i > 0) sum += i;
        }
        return sum;
    }

    virtual void run(istream & in, ostream & out)
    {
        int n = readInt(in);
        fori(n)
        {
            int nn = readInt(in);
            const vint & v = readInts(in, ' ', nn);
            out << calcSubArray(v) << ' ' << calcPosSum(v) << endl;
        }
    }
};
