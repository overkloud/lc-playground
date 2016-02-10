#include "Solution.h"

using namespace std;
/**
Given two binary trees, write a function to check if they are equal or not.
Two binary trees are considered equal if they are structurally identical and the nodes have the same value.

* Definition for binary tree
* struct TreeNode {
*     int val;
*     TreeNode *left;
*     TreeNode *right;
*     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
* };
*/
class MissingNumber : public  solution {

public:
    int missingNumber(vector<int>& nums) {
        const int n = nums.size();
        const int N = (n + 1);
        
        bool haszero = false;
        bool hasN = false;


        for(auto i : nums)
        {
            if(i % N == 0) 
            {
                haszero = true;
                nums[i % N] += N;
            }
            else if (i % N == n)
            {
                hasN = true;
                nums[0] += N;
            }
            else nums[i % N] += N;

        }

        if(!haszero) return 0;
        if(!hasN) return n;

        for(int i = 1; i < nums.size(); i++)
        {
            if(nums[i] < N)
            {
                return i;
            }
        }

        return 0;
    }

    void test()
    {
        vector<int> v{1,0};
        std::cout << missingNumber(v) << std::endl;
    }
};

