#include "Solution.h"


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
class IsSameTree : public  solution {
    struct TreeNode {
        int val;
        TreeNode *left;
        TreeNode *right;
        TreeNode(int x) : val(x), left(NULL), right(NULL) {}
        
    };
public:
    bool isSameTree(TreeNode *p, TreeNode *q) {
        using namespace std;

        if (!p && !q) return true;
        if (p && !q) return false;
        if (q && !p) return false;
        
        queue<TreeNode *>  Q;
        Q.push(q);

        queue<TreeNode *>  P;
        P.push(p);
        while (!P.empty())
        {
            if (Q.empty()) return false;
            TreeNode * p_node = P.front();
            P.pop();
            TreeNode * q_node = Q.front();
            Q.pop();

            if (p_node->val != q_node->val) return false;

            if ((p_node->left && !q_node->left) || (!p_node->left && q_node->left))
            {
                return false;
            }

            if ((p_node->right && !q_node->right) || (!p_node->right && q_node->right))
            {
                return false;
            }

            if (p_node->left && q_node->left)
            {
                P.push(p_node->left);
                Q.push(q_node->left);
            }

            if (p_node->right && q_node->right)
            {
                P.push(p_node->right);
                Q.push(q_node->right);
            }

        }

        if (P.empty() && !Q.empty()) return false;

        return true;
    }

    void test()
    {
        TreeNode p1_1(1);
        TreeNode p1_2(2);
        TreeNode p1_3(3);
        p1_1.left = &p1_2;
        p1_1.right= &p1_3;


        TreeNode q1_1(1);
        TreeNode q1_2(2);
        TreeNode q1_3(3);
        q1_1.left =  &q1_2;
        q1_1.right = &q1_3;

        assert(isSameTree(&p1_1, &q1_1));

        p1_3.val = 0;
        assert(!isSameTree(&p1_1, &q1_1));

        q1_1.right = NULL;
        assert(!isSameTree(&p1_1, &q1_1));

        p1_2.left = &p1_3;
        p1_1.right = NULL;
        q1_2.left = &q1_3;

        assert(!isSameTree(&p1_1, &q1_1));

        p1_3.val = 3;
        assert(isSameTree(&p1_1, &q1_1));
        return;
    }
};

