#include "Solution.h"

using namespace std;

class LowestCommonAncestor : public  solution {

public:

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
        TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}

    };

    struct Node
    {
        TreeNode * tree;
        Node * parent;

        Node(TreeNode * t, Node * p) :
            tree(t), parent(p)
        {
        }
    };

    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        TreeNode * result = NULL;

        if (p == q) result = p;
        else  if (p == root || q == root) result = root;
        else
        {
            queue<Node*> treeQ;
            Node * r = new Node(root, NULL);
            treeQ.push(r);
            Node * pNode;
            Node * qNode;
            while (treeQ.empty() == false)
            {
                Node * node = treeQ.front();
                treeQ.pop();

                if (node->tree->left)
                {
                    Node * l = new Node(node->tree->left, node);
                    treeQ.push(l);
                }
                if (node->tree->right)
                {
                    Node * r = new Node(node->tree->right, node);
                    treeQ.push(r);
                }

                if (node->tree == p) pNode = node;
                if (node->tree == q) qNode = node;
            }

            vt<Node*> set1;
            vt<Node*> set2;
            Node * node = pNode;
            while (node)
            {
                set1.push_back(node);
                node = node->parent;
            }
            node = qNode;
            while (node)
            {
                set2.push_back(node);
                node = node->parent;
            }

            auto itP = set1.rbegin();
            auto itQ = set2.rbegin();
            Node * last = NULL;
            while (itP != set1.rend() && itQ != set2.rend())
            {
                if ((*itP)->tree == (*itQ)->tree)
                {
                    last = *itP;
                    itP++;
                    itQ++;
                }
                else break;
            }
            result = last->tree;
        }
        return result;
    }

    virtual void test()
    {
              //_______3______
         //    /               \
       /    ___5__           ___1__
     //    /      \         /      \
    //    6      _2        0        8
           //    / \
         //     7   4

        
        TreeNode * n6 = new TreeNode(7);
        TreeNode * n7 = new TreeNode(4);
        TreeNode * n10 = new TreeNode(2,n6, n7);

        TreeNode * n8 = new TreeNode(0);
        TreeNode * n9 = new TreeNode(8);

        TreeNode * n4 = new TreeNode(6);
        TreeNode * n2 = new TreeNode(5, n4, n10);

        TreeNode * n3 = new TreeNode(1, n8, n9);
        TreeNode * n1 = new TreeNode(3, n2, n3);

        TreeNode * x = lowestCommonAncestor(n1, n2, n3);
        assert(x->val == 3);

        x = lowestCommonAncestor(n1, n6, n9);
        assert(x->val == 3);

        x = lowestCommonAncestor(n1, n10, n2);
        assert(x->val == 5);

        x = lowestCommonAncestor(n1, n2, n10);
        assert(x->val == 5);
    }
};
