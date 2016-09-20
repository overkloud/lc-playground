#include "Solution.h"

using namespace std;

class UniqueBST2: public  solution {

public:
    struct TreeNode {
        int val;
        TreeNode *left;
        TreeNode *right;
        TreeNode(int x) : val(x), left(NULL), right(NULL) {}
        
    };

    map<list<int>, vector<TreeNode*>*> M;
    vector<TreeNode*>* generateTrees(list<int> & n) {
        vector<TreeNode*>* result = new vector<TreeNode*>();

        if (n.size() == 0)
        {
            result->push_back(NULL);
        }
        else if (n.size() == 1)
        {
            TreeNode * root = new TreeNode(n.front());
            result->push_back(root);
        }
        else
        {
            if (M.find(n) != M.end())
            {
                result = M[n];
            }
            else
            {
                for (int i = 0; i < n.size(); i++)
                {
                    list<int> children(n.begin(), n.end());
                    auto it = children.begin();
                    //TreeNode * root = new TreeNode(*it);
                    std::advance(it, i);
                    int rootEle = *it;
                    auto next = children.erase(it);


                    {
                        list<int> left(children.begin(), next);
                        list<int> right(next, children.end());

                        auto leftTrees = generateTrees(left);
                        auto rightTrees = generateTrees(right);
                        for (auto leftIt = leftTrees->begin(); leftIt != leftTrees->end(); leftIt++)
                        {
                            for (auto rightIt = rightTrees->begin(); rightIt != rightTrees->end(); rightIt++)
                            {
                                TreeNode *root = new TreeNode(rootEle);
                                root->left = *leftIt;
                                root->right = *rightIt;
                                result->push_back(root);
                            }
                        }
                    }
                }
                M.emplace(n, result);
            }
            
        }

        return result;
    }
    
    vector<TreeNode*> generateTrees(int n) {
        vector<TreeNode*> result;
        list<int> list;
        fori(n)
        {
            list.push_back(i+1);
        }
        if(n != 0)
            result = *generateTrees(list);
        return result;
    }


    virtual void test()
    {
        testUtil::timer t;
        t.start();
        auto r1 = generateTrees(10);
        cout << "time spent " << t.stop() << endl;
    }
};
