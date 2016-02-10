#include "Solution.h"

using namespace std;

class UniquePaths : public  solution {

   

public:
    int uniquePaths(int m, int n)
    {
        vector<vector<int>> v;
        if(v.size() == 0)
        {
            for(int i = 0; i < m; i++)
            {
                vector<int> vv (n, -1);
                v.push_back(vv);
            }
        }

        return uniquePaths(m, n, v);
    }

    int uniquePaths(int m, int n, vector<vector<int>>& v)
    {
        if( 0 == m || 0 == n) return 0;

        if( 1 == m || 1 == n) return 1;
 
        if(v[m-1][n-1] != -1) return v[m-1][n-1];

        int sum = 0;

        cout << "calculating " << m << "," << n << endl;
        if( m == n)
            sum = 2 * uniquePaths(n - 1, m, v);
        else sum = uniquePaths( m - 1, n, v) + uniquePaths(m , n - 1, v);

        v[m-1][n-1] = sum;
        //v[n-1][m-1] = sum;
        return sum;
    }

    void test()
    {
        //vector<vector<int>> v = {{9, 8, 7}, {4, 5, 6}, {1, 2, 3}};
        //assert( 3 == uniquePaths(3, 3));
        cout << uniquePaths(13, 8) << endl;
    }
};

