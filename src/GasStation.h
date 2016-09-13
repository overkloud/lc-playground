#include "Solution.h"

using namespace std;

class GasStation: public  solution {

public:
    
    int calc(vint & v)
    {
        int start = 0;
        int sum = 0;
        fori(v.size())
        {
            sum += v[i];
        }

        if (sum < 0) return -1;


        sum = 0;
        for (int i = 0; i < v.size();)
        {
            int cur = sum + v[i];
            if (cur >= 0) { 
                i++; 
                sum = cur;
            }
            else
            {
                start = ++i;
                sum = 0;
            }
        }

        return start;
    }
    
    int canCompleteCircuit(vector<int>& gas, vector<int>& cost) {
        vint v;
        fori(gas.size())
        {
            v.push_back(gas[i] - cost[i]);
        }
        return calc(v);
    }


    virtual void test()
    {
        vint v1 = {-1, -1, 2};
        assert(2 == calc(v1));

        vint v2 = { 4,-6,4,0,-3,1};
        assert(2 == calc(v2));

        vint v3 = { 4,-6,2,0,-3,3};
        assert(5 == calc(v3));
    }
};
