#include "Solution.h"

using namespace std;

class FindMinInRotateSortedArray : public  solution {

    /***

Suppose a sorted array is rotated at some pivot unknown to you beforehand.

(i.e., 0 1 2 4 5 6 7 might become 4 5 6 7 0 1 2).

Find the minimum element.

You may assume no duplicate exists in the array.

    ***/

public:
    int findMin(vector<int>& nums, szt s, szt e) {
        szt n = nums.size();
        if (s > e) return 0;
        if (s == e) return nums[s];
        if ((e - s) == 1) return std::min(nums[e], nums[s]);

        szt mid = (e + s) / 2;
        if(nums[s] > nums[mid])
        {
            return std::min(nums[s], findMin(nums, s, mid));
        }
        else
        {
            return std::min(nums[s], findMin(nums, mid, e));
        }
    }

    int findMin(vector<int>& nums) {
        return findMin(nums, 0, nums.size() - 1);
    }

    void test()
    {
        vector<int> v = {7,8,1,2,3,4,5,6};
        cout << findMin(v) << endl;
    }
};

