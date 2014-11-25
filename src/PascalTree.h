#include "Solution.h"

//Given numRows, generate the first numRows of Pascal's triangle.
//
//For example, given numRows = 5,
//Return
//
//[
//    [1],
//    [1, 1],
//    [1, 2, 1],
//    [1, 3, 3, 1],
//    [1, 4, 6, 4, 1]
//]
using namespace std;
class PascalTree : public solution
{
public:
    vector<vector<int> > generate(int numRows) {
        vector<vector<int>> V;

        for (int i = 1; i <= numRows; i++)
        {
            vector<int> row;

            double midPoint = i / 2.0;
            for (int j = 0; j < i; j++)
            {
                vector<int> lastRow = V.back();
                if (0 == j || i - 1 == j)
                {
                    row.push_back(1);
                    continue;
                }

                // odd number of elements in this row
                if (i % 2 == 1)
                {
                    if (j == floor(midPoint))
                    {
                        
                    }
                
                }
                else
                {

                }


            }
        }



        return V;
    }
};


