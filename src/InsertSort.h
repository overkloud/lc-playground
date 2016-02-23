#include "Solution.h"

#include <time.h>


using namespace std;

class InsertSort: public  solution {

public:
    /*
    https://www.hackerrank.com/challenges/insertion-sort
    */
    int InsertionSort1(vector<int> &v)
    {
        int count = 0;

        for (int i = 0; i < v.size(); i++)
        {
            int j = i;
            while (j > 0 && v[j - 1] > v[j])
            {
                swap(v[j - 1], v[j]);
                count++;
                j--;
            }
        }
        return count;
    }


    long long InsertionSort(vector<int> &v, ll start, ll end)
    {
        if (start == end) return 0;

        if (end - start >= 2)
        {
            ll mid = (end + start) / 2;
            long long sum = InsertionSort(v, start, mid) + InsertionSort(v, mid + 1, end);
            
            if (v[mid + 1] < v[mid])
            {
                vector<int> work(end - start + 1);
                ll i = start;
                ll j = mid + 1;
                ll pos = 0;
                while (i <= mid || j <= end)
                {
                    if (i > mid)
                    {
                        work[pos++] = v[j++];
                    }
                    else if (j > end)
                    {
                        work[pos++] = v[i++];
                    }
                    else
                    {
                        if (v[i] <= v[j])
                        {
                            work[pos++] = v[i++];
                        }
                        else
                        {
                            work[pos++] = v[j++];
                            sum += (j - start - pos);
                        }
                    }
                }

                pos = start;
                for (auto it : work)
                {
                    v[pos++] = it;
                }
            }
            return sum;
        }

        long long count = 0;
        for (ll i = start; i <= end; i++)
        {
            ll j = i;
            while (j > start && v[j - 1] > v[j])
            {
                swap(v[j - 1], v[j]);
                count++;
                j--;
            }
        }
        return count;
    }

    long long InsertionSort2(vector<int> & v)
    {
        if (v.size() == 1) return 0;
        if (v.size() == 2) return v[0] <= v[1] ? 0 : 1;


        //int mid = v.size() / 2;
        return InsertionSort(v, 0, v.size() - 1);
    }

    void run(istream & in)
    {
        string line;
        int testSize = 0;
        getline(in, line);
        testSize = atoi(line.c_str());

        for (int i = 0; i < testSize; i++)
        {
            int N;
            getline(in, line);
            N = atoi(line.c_str());
            vector<int> v;
            v = readInts(in, ' ', N);
            vector<int>v1 = v;
            vector<int>v2 = v;
            time_t start;
            time(&start);

            cout << InsertionSort1(v1) << endl;
            time_t sol1;
            time(&sol1);
            cout << "Original sol: " << difftime(sol1, start) << endl;
            
            cout << InsertionSort2(v2) << endl;
            time_t sol2;
            time(&sol2);
            cout << "MergeSort sol: " << difftime(sol2, sol1) << endl;
        }
    }

    virtual void test()
    {
        ifstream in("a.in");
        run(in);
        //vector<int> v = testUtil::randomGen(100, 10);
    }
};
