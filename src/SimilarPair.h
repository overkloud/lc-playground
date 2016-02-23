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

        bool operator () (const Node * l, const Node * r) const
        {
            return l->val < r->val;
        }

    };

    typedef long long int ll;

    ll bit_q(vector<ll> & v, const int i)
    {
        ll sum = 0;
        int index = i;
        while (index > 0)
        {
            sum += v[index];
            index -= (index & ((-1) * index));
        }

        return sum;
    }

    ll bit_q(vector<ll> & v, const int i, const int j)
    {
        return bit_q(v, j) - bit_q(v, i - 1);
    }

    void bit_up(vector<ll>& v, const int val, const int index, int reverse)
    {
        //int sum = 0;
        int i = index;
        while (i <= v.size() - 1)
        {
            v[i] += (val * reverse);
            i += (i & (-1)*i);
        }
    }

    ll calcPair2(Node * root, const int k, const int n)
    {
        vector<ll> bit(n + 1, 0);
        stack<Node*> s;
        int prevLv = 0;
        //set<Node *, Node> a;
        vector<Node*> v;
        ll count = 0;
        s.push(root);
        //bit_up(bit, 1, root->val, 1);
        while (!s.empty())
        {
            auto node = s.top();
            s.pop();
            for (auto n : node->children)
                if (n->visited == false) s.push(n);
            if (!node->visited)
            {
                node->visited = true;
                int currLv = node->depth;
                if (currLv > prevLv)
                {
                    prevLv = currLv;
                    //a.insert(node->parent);
                    v.push_back(node->parent);
                    bit_up(bit, 1, node->parent->val, 1);
                }
                else if (currLv == prevLv)
                {
                }
                else
                {
                    for (int i = 0; i < prevLv - currLv; i++)
                    {
                        auto it = v.back();
                        bit_up(bit, 1, it->val, -1);
                        v.erase(v.cbegin() + v.size() - 1);
                    }
                    prevLv = currLv;
                }
                ll c = bit_q(bit, std::max(1, node->val - k), std::min(n, node->val + k));
                count += c;
            }
        }
        return count;
    }

    ll dfs(Node * root, vector<ll> & bit, const int k, const int n)
    {
        ll count = 0;
        if (root)
        {
            int i = std::max(1, root->val - k);
            int j = std::min(n, root->val + k);
            count = bit_q(bit, i, j);
            bit_up(bit, 1, root->val, 1);
            for (auto child : root->children)
            {
                count += dfs(child, bit, k, n);
            }
            bit_up(bit, 1, root->val, -1);
        }
        return count;
    }

    ll calcPair3(Node * root, const int k, const int n)
    {
        vector<ll> bit(n + 1, 0);
        return dfs(root, bit, k , n);
    }

    ll calcPair(Node * root, const int k, const int n)
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
        int max = 0;
        while (s.empty() == false)
        {
            auto node = s.top();
            s.pop();
            max = std::max(max, node->val);
            for (auto it : node->children)
                s.push(it);
            if (node->parent)
            {
                node->depth = node->parent->depth + 1;
            }
        }

        //cout << calcPair(root, k, max) << endl;
        cout << calcPair3(root, k, max) << endl;
    }

    virtual void test()
    {
        ifstream in("a.in");
        run(in);
    }
};
