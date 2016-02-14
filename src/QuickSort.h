#include "Solution.h"

using namespace std;

class QuickSort: public  solution {

public:

    int partition(vector<int> & v, const int lo, const int hi)
    {
        if (lo < hi)
        {
            int swapPoint = lo;
            int p = hi;
            for (int i = lo; i < hi; i++)
            {
                if (v[i] < v[p])
                {
                    std::swap(v[i], v[swapPoint]);
                    swapPoint++;
                }
            }
            std::swap(v[p], v[swapPoint]);
            return swapPoint;
        }
        else return lo;
    }

    void quickSort(vector<int> & v, const int lo, const int hi)
    {
        if (lo < hi)
        {
            int p = partition(v, lo, hi);
            print(v);
            quickSort(v, lo, p - 1);
            quickSort(v, p + 1, hi);
        }
    }

    void quickSort(vector<int> & v)
    {
        quickSort(v, 0, v.size() - 1);
    }

    void run(istream & in, ostream & out)
    {
        string line;
        getline(in, line);
        int count = atoi(line.c_str());
        getline(in, line);
        vector<string> vs = split(line, ' ');
        vector<int> vi;
        for (int i = 0; i < count; i++)
        {
            vi.push_back(atoi(vs[i].c_str()));
        }
        quickSort(vi);
    }

    virtual void test()
    {
        ifstream in("a.in");
        run(in, std::cout);
    }
};
