#include "Solution.h"

using namespace std;

/*
https://www.hackerrank.com/challenges/matrix-rotation-algo
You are given a 2D matrix, a, of dimension MxN and a positive integer R. You have to rotate the matrix R times and print the resultant matrix. Rotation should be in anti-clockwise direction.

Rotation of a 4x5 matrix is represented by the following figure. Note that in one rotation, you have to shift elements by one step only (refer sample tests for more clarity).
*/

class MatrixRotation: public  HRsolution {

public:


    typedef vector<vector<int>> Matrix;


    // rotate 4 edges of the Rectangle, starting at position (i, j) for size m * n
    Matrix & rotate4Edges(Matrix &M, const ll i, const ll j, const ll m, const ll n)
    {
        if (m <= 1 || n <= 1) return M;

        int temp;
        int t1;
        int leftdown = M[i + m - 1][j];
        int rightup = M[i][j + n -1];
        int rightdown = M[i + m - 1][j + n -1];
        int leftup = M[i][j];

        if (m >= 3)
        {
            temp = M[i + 1][j];
            for (ll x = i + 2; x <= i + m - 1; x++)
            {
                t1 = M[x][j];
                M[x][j] = temp;
                temp = t1;
            }
            temp = M[i + m - 2][j + n - 1];
            for (ll x = i + m - 3; x >= i; x--)
            {
                t1 = M[x][j + n - 1];
                M[x][j + n - 1] = temp;
                temp = t1;
            }

        }

        if (n >= 3) 
        {
            temp = M[i + m - 1][j + 1];

            for (ll x = j + 2; x <= j + n - 1; x++)
            {
                t1 = M[i + m - 1][x];
                M[i + m - 1][x] = temp;
                temp = t1;
            }
            temp = M[i][j + n - 2];
            for (ll x = j + n - 3; x >= j; x--)
            {
                t1 = M[i][x];
                M[i][x] = temp;
                temp = t1;
            }
        }
        M[i + 1][j] = leftup;
        M[i][j + n - 2] = rightup;
        M[i + m - 1][j + 1] = leftdown;
        M[i + m - 2][j + n -1] = rightdown;
        return M;
    }

    Matrix & rotate(Matrix & M, const int r)
    {
        if (M.size() == 0 || M[0].size() == 0) return M;

        ll m = M.size();
        ll n = M[0].size(); 
        int i = 0;
        int j = 0;

        while (m > 0 && n > 0)
        {
            szt x = 2 * (m + n) - 4;
            int t = r % x;
            for (int p = 0; p < t; p++)
                rotate4Edges(M, i, j, m, n);
            i++; j++;
            m -= 2; n -= 2;
        }

        return M;
    }

    void run(istream & in, ostream & out)
    {
        string line;
        int m, n, r;
        Matrix M;
        if (in.good() && in.eof() == false)
        {
            std::getline(in, line);
            if (line.empty() == false)
            {
                vector<string> v = split(line.c_str(), ' ');
                m = atoi(v[0].c_str());
                n = atoi(v[1].c_str());
                r = atoi(v[2].c_str());
            }
            for (int i = 0; i < m; i++)
            {
                getline(in, line);
                vector<string> v = split(line, ' ');
                vector<int> v1;
                std::for_each(v.begin(), v.end(), [&v1](string s)
                {
                    v1.push_back(atoi(s.c_str()));
                });
                M.push_back(v1);
            }
        }

        //print(M);
        //int c = 2 * (m + n) - 4;
        //r = r % c;
        rotate(M, r);
        print(M);
    }

    virtual void test()
    {
        ifstream file("a.in");
        run(file, std::cout);
    }
};
