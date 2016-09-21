#include "Solution.h"

using namespace std;

class UniquePath2: public  solution {

public:

    int uniquePathsWithObstacles(vector<vector<int>>& v, szt m, szt n) {

        if(v[m][n] != 0)
        {
            if (m == 0 && n == 0)
            {
                v[0][0] = 1;
            }
            else if (m == 0)
            {
                uniquePathsWithObstacles(v, m, n - 1);
                v[m][n] = v[m][n - 1];
            }
            else if (n == 0)
            {
                uniquePathsWithObstacles(v, m - 1, n);
                v[m][n] = v[m - 1][n];
            }
            else if (v[m][n] != -1);
            else
            {
                v[m][n] = uniquePathsWithObstacles(v, m - 1, n)+ uniquePathsWithObstacles(v, m, n-1);
            }
        }
        return  v[m][n];
    }
    
    int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid) {
        int sum = 0;
        szt m = obstacleGrid.size();
        if (m != 0)
        {
            szt n = obstacleGrid[0].size();
            if (n != 0)
            {
                for (vint & row : obstacleGrid)
                {
                    for (int & ele : row)
                    {
                        if (ele == 1)
                        {
                            ele = 0;
                        }
                        else if (ele == 0)
                        {
                            ele = -1;
                        }
                    }
                }
                sum = uniquePathsWithObstacles(obstacleGrid, m-1, n-1);
            }
        }
        return sum;
    }


    virtual void test()
    {
        vt<vint> v0 = { { 0,0,0 },{ 0,1,0 },{ 0,0,0 } };
        int r0 = uniquePathsWithObstacles(v0);

        vt<vint> v1 = { {1,0,0},{0,1,0},{0,0,0} };
        int r1 = uniquePathsWithObstacles(v1);

        vt<vint> v2 = { { 0,0,0 }};
        int r2 = uniquePathsWithObstacles(v2);

        vt<vint> v3 = { { 1,0,0 } };
        int r3 = uniquePathsWithObstacles(v3);

        vt<vint> v4 = { { } };
        int r4 = uniquePathsWithObstacles(v4);
    }
};
