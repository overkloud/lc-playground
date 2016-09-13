#include "Solution.h"

using namespace std;

class SearchRange: public  solution {

public:

    void calc(vint & v, const int target, const int start, const int end, vint & result)
    {
        function<void(int)> updateResult = [&result, &v](int index)
        {
            if (result[0] == -1 || index < result[0])
            {
                result[0] = index;
            }
            if (index > result[1])
            {
                result[1] = index;
            }
        };

        if (start == end)
        {
            if (v[start] == target)
            {
                updateResult(start);
            }
        }
        else if(start < end)
        {
            int mid = (start + end) / 2;
            if (v[mid] == target)
            {
                updateResult(mid);
                calc(v, target, start, mid, result);
                calc(v, target, mid + 1, end, result);
            }
            else if (v[mid] < target)
            {
                calc(v, target, mid + 1, end, result);
            }
            else
            {
                calc(v, target, start, mid, result);
            }
        }
    }

    vint calc(vint & nums, int target)
    {
        vint result(2,-1);
        calc(nums, target, 0, (int)nums.size(), result);
        return result;
    }

    vint slow_search(vint& nums, int target)
    {
        vint result;
        bool found = false;
        fori(nums.size())
        {
            if (nums[i] == target)
            {
                if (!found)
                {
                    found = true;
                    result.push_back(i);
                    result.push_back(i);
                }
                else
                {
                    result[1] = i;
                }
            }
        }
        if (result.size() == 0)
        {
            result.push_back(-1);
            result.push_back(-1);
        }
        return result;
    }

    vector<int> searchRange(vector<int>& nums, int target) {
        return calc(nums, target);
    }

    virtual void test()
    {
        vint v = { 5, 7, 7, 8, 8, 10 };
        vint r = slow_search(v, 8);

        int numTest = 5;
        fori(numTest)
        {
            vint v = testUtil::randomGen(100000,300,false);
            int target = testUtil::randomGen(1, 30, false)[0];
            sort(v.begin(), v.end());
            testUtil::timer t;
            t.start();
            vint r1 = slow_search(v, target);
            cout << t.stop() << endl;
            t.reset();
            vint r2 = searchRange(v, target);
            cout << t.stop() << endl;
            assert(r1.size() == r2.size());
            assert(r1.size() == 2);
            for (int j = 0; j < r1.size(); j++)
            {
                assert(r1[j] == r2[j]);
            }
        }
    }
};
