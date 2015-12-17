#include "Solution.h"

using namespace std;

/**
Given a binary search tree, write a function kthSmallest to find the kth smallest element in it.

Note:
You may assume k is always valid, 1 ¡Ü k ¡Ü BST's total elements. 
**/

class KthSmallest: public  solution {

    struct TreeNode {
        int val;
        TreeNode *left;
        TreeNode *right;
        TreeNode(int x) : val(x), left(NULL), right(NULL) {}
        //int size;
    };
    typedef TreeNode Node;

public:

    map<Node*, int> M;

    void countAllChildren(Node * root)
    {
        if (NULL == root) return;
        
        int size = 0;
        countAllChildren(root->left);
        countAllChildren(root->right);
        
        if (root->left) size += 1 + M[root->left];
        if (root->right) size += 1 + M[root->right];

        M.insert(make_pair(root, size));
    }

    int searchForK(Node * root, int k)
    {
        if (NULL == root) return 0;

        if (root->left)
        {
            if (M.find(root->left) == M.end())
                countAllChildren(root->left);

            int n = M[root->left] + 1;
            if (n == k - 1)
                return root->val;
            else if (k > n + 1)
                return searchForK(root->right, k - n - 1);
            else if (k < n + 1)
                return searchForK(root->left, k);
        }
        else
        {
            if (1 == k) return root->val;
            else return searchForK(root->right, k - 1);
        }
    }


    int i = 0;
    int ret = 0;
    int kthSmallest(TreeNode* root, int k) {
        //countAllChildren(root);
        //return searchForK(root, k);
        if (root)
        {
            if (ret == 0) kthSmallest(root->left, k);
            i++;
            if (k == i)
            {
                ret = root->val;
                return ret;
            }
            if (ret == 0) kthSmallest(root->right, k);
        }
        return ret;
    }

    virtual void test()
    {
        TreeNode *r1 = new TreeNode(3);
        TreeNode *r2 = new TreeNode(1);
        TreeNode *r3 = new TreeNode(4);
        TreeNode *r4 = new TreeNode(2);

        r1->left = r2;
        r1->right = r3;
        r2->right = r4;
        cout << kthSmallest(r1, 2) << endl;
    }
};
