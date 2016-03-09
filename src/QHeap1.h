#include "Solution.h"

using namespace std;

class QHeap1: public  solution {

public:


    void min_heapify(vint & h, int n, int i)
    {
        int r = i;
        while (r <= n / 2)
        {
            int min = r;
            if (2*r <=n && h[r] > h[2 * r]) {
                min = 2 * r;
            }
            if (2*r + 1 <= n)
            {
                if (h[min] > h[2 * r + 1])
                    min = 2 * r + 1;
            }

            if (min == r)
                break;
            
            std::swap(h[min], h[r]);
            r = min;
        }
    }

    int find(vint & h, int n, int x, int r)
    {
        if (n == 0) return 0;

        if (n == 1) return h[1] == x ? 1 : 0;
        
        if (x < h[r]) return 0;

        if (x == h[r]) return r;

        if (2 * r <= n && h[2 * r] <= x)
        {
            int found = find(h, n, x, 2 * r);
            if (found) return found;
        }
        if (2 * r + 1 <= n && h[2 * r + 1] <= x)
        {
            int found = find(h, n, x, 2 * r + 1);
            if (found) return found;
        }
        return 0;
    }

    int min(vint & h, int n)
    {
        if(n >= 1)
            return h[1];
        else return 0;
    }

    void insert(vint &h, int & n, int x)
    {
        h[++n] = x;
        int r = n;
        while (r > 1 && h[r] < h[r/2])
        {
            std::swap(h[r], h[r / 2]);
            r = r / 2;
        }
    }

    void remove(vint & h, int & n, int x)
    {
        int pos = find(h, n, x, 1);
        if (pos != 0)
        {
            swap(h[n--], h[pos]);
            min_heapify(h, n, pos);
        }
    }    


    void run(vt<vint> & v)
    {
        vint h(v.size() + 1, 0);
        int n = 0;
        for (auto it : v)
        {
            if (it.size() == 1 && it[0] == 3)
            {
                cout << min(h, n) << endl;
            }
            else if (it.size() == 2)
            {
                if (it[0] == 1)
                {
                    insert(h, n, it[1]);
                }
                else
                {
                    remove(h, n, it[1]);
                }
            }
        }
    }


    virtual void run(istream & in)
    {
        int q = readInt(in);
        vt<vint> v;
        for (int i = 0; i < q; i++)
        {
            v.push_back(readInts(in));
        }
        run(v);
    }
};
