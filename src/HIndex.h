#include "Solution.h"

using namespace std;

class HIndex: public  solution {

public:

    int calc(vint & v, int start, int end, int h)
    {
        int result = 0;
        if (end > start)
        {
            if (start == end) result = 0;
            else if (end == start + 1)
            {
                if (1 + h >= v[start]) result = v[start];
                else result = v[start] > 0 ? 1+h : h;
            }
            else if (end == start + 2)
            {
                result = std::max(std::min(h+1, v[start+1]), std::min(h+2, v[start]));
                /*if (h + 1 >= v[start + 1]) result = v[start + 1];
                else if (h + 2 >= v[start]) result = v[start];*/
            }
            else
            {
                int mid = (end + start) / 2;
                int count = end - mid;
                if (count + h >= v[mid])
                {
                    result = std::max(v[mid], calc(v, mid, end, h));
                }
                else
                {
                    result = std::max(count + h, calc(v, start, mid, count + h));
                }
            }
        }
        return result;
    }

    int hIndex(vector<int>& citations) {
        if (citations.size() == 0)return 0;
        sort(citations.begin(), citations.end());
        return calc(citations,  0, (int)citations.size(), 0); 
    }

    virtual void test()
    {
        vint v0 = { 1 };
        assert(hIndex(v0) == 1);

        vint v1 = { 2 };
        assert(hIndex(v1) == 1);

        vint v2 = {2 ,3};
        assert(hIndex(v2) == 2);

        vint v3 = { 3 ,4 };
        assert(hIndex(v3) == 2);

        vint v4 = { 3,0,6,1,5};
        assert(hIndex(v4) == 3);

        vint v5 = { 0,1,3,3,3 };
        assert(hIndex(v5) == 3);

        vint v6 = { 0,0,0,2,2 };
        assert(hIndex(v6) == 2);

        vint v7 = { 1,2,8,8,8 };
        assert(hIndex(v7) == 3);

        vint v8 = { 2,4,8,9,9,3 };
        assert(hIndex(v8) == 4);
    }
};
