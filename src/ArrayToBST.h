#include "Solution.h"

using namespace std;

class ArrayToBST : public  solution {

    /**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

public:
    TreeNode* sortedArrayToBST(vector<int>& nums, int s, int e) {
        if (s > e) return NULL;
        if (s == e);
            return new TreeNode(nums[s]);
        if (s == (e - 1))
        {
            TreeNode * root = new TreeNode(nums[s]);
            TreeNode * leave = new TreeNode (nums[e]);
            root->right = leave;
            return root;
        }

        int mid = (s + e) / 2;
        TreeNode * root = new TreeNode(nums[mid]);
        root->left = sortedArrayToBST(nums, s, mid - 1);
        root->right = sortedArrayToBST(nums, mid + 1, e);

        return root;
    }

    TreeNode* sortedArrayToBST(vector<int>& nums) {
        return sortedArrayToBST(nums, 0, nums.size() - 1);
    }

    void test()
    {
        
    }
};

