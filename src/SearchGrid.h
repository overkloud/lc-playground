#include "Solution.h"

using namespace std;

class SearchGrid: public  solution {


    /*
    https://www.hackerrank.com/challenges/the-grid-search
    Given a 2D array of digits, try to find the occurrence of a given 2D pattern of digits. For example, consider the following 2D matrix:

    1234567890
    0987654321
    1111111111
    1111111111
    2222222222
    Assume we need to look for the following 2D pattern:

    876543
    111111
    111111
    If we scan through the original array, we observe that the 2D pattern begins at the second row and the third column of the larger grid (the 88 in the second row and third column of the larger grid is the top-left corner of the pattern we are searching for).

    So, a 2D pattern of PP digits is said to be present in a larger grid GG, if the latter contains a contiguous, rectangular 2D grid of digits matching with the pattern PP, similar to the example shown above.

    Input Format
    The first line contains an integer, TT, which is the number of test cases. TT test cases follow, each having a structure as described below:
    The first line contains two space-separated integers, RR and CC, indicating the number of rows and columns in the grid GG, respectively.
    This is followed by RR lines, each with a string of CC digits, which represent the grid GG.
    The following line contains two space-separated integers, rr and cc, indicating the number of rows and columns in the pattern grid PP.
    This is followed by rr lines, each with a string of cc digits, which represent the pattern PP.
    */

    

public:
    typedef vector<vector<int>> Grid;
    bool gridMatch(const Grid &A, int i, int j, const Grid &B)
    {
        if (A.empty() || B.empty()) return false;
        int A_row = A.size();
        int A_col = A[0].size();
        int B_row = B.size();
        int B_col = B[0].size();

        if (A_row - i < B_row) return false;
        if (A_col - j < B_col) return false;

        for (int x = 0; x < B_row; x++)
        {
            for (int y = 0; y < B_col; y++)
            {
                if (A[x + i][y + j] != B[x][y])
                    return false;
            }
        }

        return true;
    }

    bool searchGrid(const Grid & A, const Grid & B)
    {
        if (A.empty() || B.empty()) return false;
        if (A[0].empty() || B[0].empty()) return false;
        int A_row = A.size();
        int A_col = A[0].size();
        int B_row = B.size();
        int B_col = B[0].size();

        for (int i = 0; i < A.size(); i++)
        {
            for (int j = 0; j < A[0].size(); j++)
            {
                if (A[i][j] == B[0][0] && i + B_row <= A_row && j + B_col <= A_col)
                {
                    if (gridMatch(A, i, j, B)) return true;
                }
            }
        }
        return false;
    }
    
    virtual void test()
    {

    }
};
