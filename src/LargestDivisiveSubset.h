#include "Solution.h"

using namespace std;

class LargestDivisiveSubset: public  solution {

public:
    
    vint largestDivisibleSubset(vint & nums) {
        sint s;
        for (auto i : nums)
        {
            s.insert(i);
        }
        sint s2 = largestDivisibleSubset(s);
        vint v;
        for (auto i : s2)
        {
            v.push_back(i);
        }
        return v;
    }

    set<int> largestDivisibleSubset(set<int>& nums) {
        map<int, set<int>> m;
        map<int, int>t;

        if (nums.size() <= 1)
        {
            return std::move(nums);
        }
        else if (2 == nums.size())
        {
            auto it = nums.begin();
            auto i1 = *it;
            auto i2 = *(++it);
            int min = std::min(i1, i2);
            int max = std::max(i1, i2);
            set<int> v;
            if (max % min == 0)
                return std::move(nums);
            else
            {
                v.insert(min);
                return std::move(v);
            }
        }

        for (auto it = nums.rbegin(); it != nums.rend(); it++)
        {
            auto x = *it;
            if (t.find(x) == t.end())
            {
                auto iterator = it;
                for (auto jt = ++iterator; jt != nums.rend(); jt++)
                {
                    auto y = *jt;
                    if (x % y == 0)
                    {
                        auto it = m.find(x);
                        if (it == m.end())
                        {
                            set<int> s1;
                            s1.insert(y);
                            m.emplace(x, s1);
                        }
                        else
                        {
                            it->second.insert(y);
                        }
                        t.emplace(y, x);
                    }
                }
            }
        }

        sint result;
        if (m.size() != 0)
        {
            int count = 0;
            szt max = 0;
            
            int i;
            for (auto s : m)
            {
                auto set = s.second;
                sint && v1 = largestDivisibleSubset(set);
                if (v1.size() > max)
                {
                    i = s.first;
                    max = v1.size();
                    result.clear();
                    for (auto ele : v1) result.insert(ele);
                }
            }

            result.insert(i);
        }
        else
        {
            result.insert(*nums.begin());
        }
        
        return result;
    }


    virtual void test()
    {
        vint v = {1,2,3,4,5,6,24};
        auto i = largestDivisibleSubset(v);

        vint v2 = { 1,2,4,8};
        auto i2 = largestDivisibleSubset(v2);

        vint v3 = { 1,2,3 };
        auto i3 = largestDivisibleSubset(v3);

        vint v4 = { 2,3,5 };
        auto i4 = largestDivisibleSubset(v4);
    }
};
