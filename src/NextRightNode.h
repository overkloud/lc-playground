#include "Solution.h"

using namespace std;

class NextRightNode : public  solution {

 /**
 * Definition for binary tree with next pointer.
 * struct TreeLinkNode {
 *  int val;
 *  TreeLinkNode *left, *right, *next;
 *  TreeLinkNode(int x) : val(x), left(NULL), right(NULL), next(NULL) {}
 * };
 */

 struct TreeLinkNode {
  int val;
  TreeLinkNode *left, *right, *next;
  TreeLinkNode(int x) : val(x), left(NULL), right(NULL), next(NULL) {}
 };

public:

    void connect(TreeLinkNode *root) {

        if(NULL == root) return;

        queue<TreeLinkNode*> q;
        q.push(root);
        while(!q.empty())
        {
            auto n = q.front();
            q.pop();
            if(n->left && n->right)
            {
                n->left->next = n->right;
                if(n->next)
                {
                    n->right->next = n->next->left;
                }

                if(n->left->left && n->left->right) q.push(n->left);
                if(n->right->left && n->right->right) q.push(n->right);
            }

        }
    }
    
    void test()
    {
        //connect()
    }
};

