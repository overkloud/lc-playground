#include "Solution.h"

using namespace std;

class Triangle: public  solution {

public:
    // https://leetcode.com/problems/triangle/
    /*

    Given a triangle, find the minimum path sum from top to bottom. Each step you may move to adjacent numbers on the row below.

    For example, given the following triangle
    [
    [2],
    [3,4],
    [6,5,7],
    [4,1,8,3]
    ]
    The minimum path sum from top to bottom is 11 (i.e., 2 + 3 + 5 + 1 = 11).
    */

    int minimumTotal(vector<vector<int>>& triangle, int dep, vint &currentBest) {
        if (dep == triangle.size() - 1)
        {
            for (auto i : triangle[dep])
            {
                currentBest.push_back(i);
            }
        }
        else
        {
            vint prev;
            minimumTotal(triangle, dep + 1, prev);
            range(dep + 1)
            {
                int sum = std::min(prev[i], prev[i + 1]) + triangle[dep][i];
                currentBest.push_back(sum);
            }
        }

        return 0;
    }

    int minimumTotal(vector<vector<int>>& triangle) {

        if (triangle.size() == 0) return 0;

        vint v;
        minimumTotal(triangle, 0, v);
        return v[0];
    }

    virtual void test()
    {
        vt<vint> v = { {1},{2,3} };
        assert(3 == minimumTotal(v));

        vt<vint> v2 = { { 1 }};
        assert(1 == minimumTotal(v2));

        vt<vint> v3 = { };
        assert(0 == minimumTotal(v3));

        vt<vint> v4 = { {2}, {3,4}, {6,5,7}, {4,1,8,3}};
        assert(11 == minimumTotal(v4));
    }
};
