#include "Solution.h"

using namespace std;

class SimilarPair: public  solution {

public:

    struct Node
    {
        int val;
        vector<Node*> children;
        Node * parent;
        int depth;
        bool visited = false;
        Node(){};
        Node(int v, Node * parent, int dep)
        {
            this->val = v;
            this->depth = dep;
            this->parent = parent;
            visited = false;
        }

        void addC(Node * c)
        {
            children.push_back(c);
        }

        bool operator < (const Node & n) const
        {
            return this->val < n.val;
        }

        bool operator < (const Node *& n) const
        {
            return this->val < n->val;
        }

        bool operator == (const Node & n) const
        {
            return this->val < n.val;
        }


        bool operator () (const Node & l, const Node & r) const
        {
            return l.val < r.val;
        }

        bool operator () (const Node * l, const Node * r) const
        {
            return l->val < r->val;
        }

    };

    typedef long long int ll;

    ll calcPair(Node * root, const int k)
    {
        stack<Node*> s;
        int prevLv = 0;
        set<Node *, Node> a;
        vector<Node*> v;
        ll count = 0;
        s.push(root);
        while (!s.empty())
        {
            auto node = s.top();
            s.pop();
            for (auto n : node->children)
                if(n->visited == false) s.push(n);
            if (!node->visited)
            {
                node->visited = true;
                int currLv = node->depth;
                if (currLv > prevLv)
                {
                    prevLv = currLv;
                    a.insert(node->parent);
                    v.push_back(node->parent);
                }
                else if (currLv == prevLv)
                {
                    //auto it = a.find(node->parent);
                    //if (it == a.end())
                    //{
                    //    a.insert(node->parent)
                    //}
                }
                else
                {
                    for (int i = 0; i < prevLv - currLv; i++)
                    {
                        auto it = v.back();
                        a.erase(it);
                        v.erase(v.cbegin() + v.size() - 1);
                    }
                    prevLv = currLv;
                }
                Node * targetNode = new Node(std::max(node->val - k,1), NULL, 0);
                auto find = a.lower_bound(targetNode);
                {
                    while (find != a.end() && (*find)->val <= node->val + k)
                    {
                        count++;
                        find++;
                    }
                }
            }
        }
        return count;
    }

    void run(istream & in)
    {
        vector<int> v = readInts(in, ' ', 2);
        int n = v[0];
        int k = v[1];
        //set<Node*, Node> s;
        const int N = 100001;
        vector<Node*> a(N, nullptr);
        for (auto it : a)
            it = nullptr;

        Node * root = nullptr;


        for (int i = 0; i < n - 1; i++)
        {
            v = readInts(in, ' ', 2);
            int val = v[0];
            int c = v[1];
            Node * parent;
            Node * child; 
            if (nullptr == a[val])
            {
                parent = new Node(val, nullptr, 0);
                a[val] = parent;
            }
            else
            {
                parent = a[val];
            }
            if (nullptr == a[c])
            {
                child = new Node(c, parent, parent->depth + 1);
                parent->children.push_back(child);
                a[c] = child;
            }
            else
            {
                child = a[c];
                child->parent = parent;
                child->depth = parent->depth + 1;
                parent->children.push_back(child);
            }
        }

        for (auto it : a)
        {
            if (it && it->parent == nullptr)
            {
                root = it;
                break;
            }
        }

        stack<Node*> s;
        s.push(root);
        while (s.empty() == false)
        {
            auto node = s.top();
            s.pop();
            for (auto it : node->children)
                s.push(it);
            if (node->parent)
            {
                node->depth = node->parent->depth + 1;
            }
        }

        cout << calcPair(root, k) << endl;
    }

    virtual void test()
    {
        ifstream in("a.in");
        run(in);
    }
};
