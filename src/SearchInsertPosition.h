#include "Solution.h"

//Given a sorted array and a target value, return the index if the target is found.If not, return the index where it would be if it were inserted in order.
//
//You may assume no duplicates in the array.
//
//Here are few examples.
//[1, 3, 5, 6], 5 -> 2
//[1, 3, 5, 6], 2 -> 1
//[1, 3, 5, 6], 7 -> 4
//[1, 3, 5, 6], 0 -> 0
using namespace std;
class SearchInsertPosition : public solution
{

public:
    int searchInsert(int A[], int n, int target) {
        int firstLargerPos = -1;

        if (n == 0) return 1;

        for (int i = 0; i < n; i++)
        {
            if (A[i] == target) return i;

            if (A[i] > target)
            {
                firstLargerPos = i;
                break;
            }
        }

        if (firstLargerPos == -1)
            return n;
        return firstLargerPos;
    }

    void test()
    {
        assert(1 == searchInsert(vector<int>({}).data(), 0, 5));
        assert(0 == searchInsert(vector<int>({1}).data(), 1, 0));
        assert(1 == searchInsert(vector<int>({ 1 }).data(), 1, 2));
        assert(2 == searchInsert(vector<int>({ 1, 3, 5, 6 }).data(), 4, 5));
        assert(1 == searchInsert(vector<int>({ 1, 3, 5, 6 }).data(), 4, 2));
        assert(4 == searchInsert(vector<int>({ 1, 3, 5, 6 }).data(), 4, 7));
        assert(0 == searchInsert(vector<int>({ 1, 3, 5, 6 }).data(), 4, 0));
    }
};

