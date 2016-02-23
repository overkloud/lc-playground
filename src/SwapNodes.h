#include "Solution.h"

using namespace std;

class SwapNodes: public  solution {

public:


    // root start at v[1]
    void printInOrder(vector<vint> & v, int pos)
    {
        if (pos >= 1 && pos < v.size())
        {
            int left = v[pos][0];
            int right= v[pos][1];
            if (left != -1) printInOrder(v, left);
            cout << pos << " ";
            if (right != -1) printInOrder(v, right);
        }
        
    }

    void printInOrder(vector<vint> & v)
    {
        printInOrder(v, 1);
        cout << endl;
    }

    void swap(vector<vint> & v, int index)
    {
        std::swap(v[index][0], v[index][1]);
    }

    void run(vector<vint> &v, vint k)
    {
        map<int, vint> d;
        vint dv(v.size(), 0);
        int maxDepth;

        if (v.size() != 0)
        {
            dv[1] = 1;
            maxDepth = 1;
            vint one = { 1 };
            d.emplace(1, one);
        }

        for (int i = 1; i < v.size(); i++)
        {
            vint va; 
            int parentDepth = dv[i];
            int depth = parentDepth + 1;
                if (v[i][0] != -1) {
                    int left = v[i][0];
                    va.push_back(left);
                    dv[left] = depth;
                }
                if (v[i][1] != -1) {
                    int right = v[i][1];
                    va.push_back(right);
                    dv[right] = depth;
                }
                auto it = d.find(depth);
                if (it != d.end()) {
                    it->second.insert(it->second.end(), va.begin(), va.end());
                }
                else d.emplace(depth, va);
        }
        maxDepth = d.rbegin()->first;

        for (auto s : k)
        {
            for (int i = 1; i*s <= maxDepth; i++)
            {
                int depth = i*s;
                auto it = d.find(depth);
                if (it != d.end())
                {
                    for (auto n : it->second)
                    {
                        swap(v, n);
                    }
                }
            }
            printInOrder(v);
        }
    }


    void run(istream & in)
    {
        int n = readInt(in);
        vector<vint> v(n + 1);
        for (int i = 1; i <= n; i++)
        {
            //v[1].push_back
            string line;
            getline(in, line);
            vint a = splitToInts(line, ' ');
            for (auto j : a)
            {
                v[i].push_back(j);
            }
        }
        int t = readInt(in);
        vint k;
        for (int i = 0; i < t; i++)
        {
            k.push_back(readInt(in));
        }
        run(v, k);
    }
};
