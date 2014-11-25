#include "Solution.h"



/**
Given a binary tree, find its maximum depth.
The maximum depth is the number of nodes along the longest path from the root node down to the farthest leaf node.
* Definition for binary tree
* struct TreeNode {
*     int val;
*     TreeNode *left;
*     TreeNode *right;
*     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
* };
*/
using namespace std;
class MaxDepth : public  solution {
    struct TreeNode
    {
        int val;
        TreeNode *left;
        TreeNode *right;
        TreeNode(int x) : val(x), left(NULL), right(NULL) {}
    };

public:
    int maxDepth(TreeNode *root) {
        using namespace std;
        root->val = 1;
        queue<TreeNode*> Q;
        Q.push(root);
        int maxDepth = 1;
        while (!Q.empty())
        {
            auto node = Q.front();
            Q.pop();
            auto left = node->left;
            auto right = node->right;

            if (left)
            {
                left->val = node->val + 1;
                Q.push(left);
                if (left->val > maxDepth) maxDepth = left->val;
            }
            if (right)
            {
                right->val = node->val + 1;
                Q.push(right);
                if (right->val > maxDepth) maxDepth = right->val;
            }
        }

        return maxDepth;
    }

    void test()
    {
        TreeNode t1(0); 
        assert(1 == maxDepth(&t1));


        TreeNode t2(0);
        TreeNode t3(0);
        TreeNode t4(0);
        t2.left = &t3;
        t2.right= &t4;
        assert(2 == maxDepth(&t2));
    }
};
