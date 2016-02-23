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
    ll missingNumber(vector<ll>& nums) {
        const size_t n = nums.size();
        const szt N = (n + 1);
        
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
        if(!hasN) return (ll)n;

        for(int i = 1; i < nums.size(); i++)
        {
            if(nums[i] < (ll)N)
            {
                return i;
            }
        }

        return 0;
    }

    void test()
    {
        vector<ll> v{1,0};
        std::cout << missingNumber(v) << std::endl;
    }
};

