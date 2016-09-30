#include "Solution.h"

using namespace std;

class MinPathSum: public  solution {

public:

    //map<pair<int, int>, int> mmap;
    vvint mmap;
    int minPathSum(vector<vector<int>>& grid, const int m, const int n, const int row, const int col) {
        int result = 0;
        auto cur = grid[m][n];

        if (m == row && n == col)
        {
            return result + cur;
        }
        else if (m == row)
        {
            auto prv = mmap[m][n+1];
            if(prv == -1)
                result = minPathSum(grid, m, n + 1, row, col) + cur;
            else result = prv + cur;
        }
        else if (n == col)
        {
            auto prv = mmap[m+1][n];
            if (prv == -1)
                result = minPathSum(grid, m+1, n, row, col) + cur;
            else result =prv+ cur;
        }
        else
        {
            auto prv1 = mmap[m + 1][n];
            auto prv2 = mmap[m][n+1];
            int p1 = 0;
            int p2 = 0;
            if (prv1 == -1)
                p1 = minPathSum(grid, m + 1, n, row, col);
            else p1 = prv1;
            if (prv2 == -1)
                p2 = minPathSum(grid, m, n + 1, row, col);
            else p2 = prv2;

            auto prev = std::min(p1,p2);
            result = prev + cur;
        }

        mmap[m][n] = result;

        return result;
    }

    int minPathSum(vector<vector<int>>& grid) {
        int result = 0;
        if (grid.size() != 0 && grid[0].size() != 0)
        {
            int row = (int)grid.size() - 1;
            int col = (int)grid[0].size() - 1;
            mmap.clear();
            range(row+1)
            {
                vint v(col+1, -1);
                mmap.push_back(v);
            }

            result = minPathSum(grid, 0, 0, row, col);
        }

        return result;
    }

    virtual void test()
    {
        int vectorRow = 100;
        vvint vv;
        range(vectorRow)
        {
            vint v = testUtil::randomGen(100, 40, false);
            std::this_thread::sleep_for(100ms);
            vv.push_back(v);
        }
        testUtil::timer t;
        t.start();
        /*for (auto e : vv)
            vector2Stream(cout, e);*/
        auto r = minPathSum(vv);
        cout << t.stop() << endl;
    }
};
