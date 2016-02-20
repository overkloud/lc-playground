#include "Solution.h"

using namespace std;

class ScalarProduct: public  solution {

public:


    void calcVector(const int C, const int M, const int N, vector <long long> & v, set<long long> &p)
    {
        vector<long long> a;
        a.push_back(0);
        a.push_back(C);

        int a2, a3;
        bool looped = false;
        int lastIndex = 2 * N + 1;
        for (int i = 2; i < 2 * N + 2; i++)
        {
            int x = (a[i - 2] + a[i - 1]) % M;

            if (i == 2) {
                a2 = x;
            }
            else if (3 == i) {
                a3 = x;
            }
            else
            {
                if (x == a3 && a[i - 1] == a2)
                {
                    if (i % 2 == 1) {
                        a.push_back(x);
                        lastIndex = i;
                        break;
                    }
                    else
                    {
                    }
                }

            }
            a.push_back(x);
        }

        for (int i = 2; i <= lastIndex - 3; i = i + 2)
        {
            for (int j = i + 2; j <= lastIndex - 1; j = j + 2)
            {
                long long x = a[i] * a[j] + a[i + 1] * a[j + 1];
                p.insert(x % M);
                if (p.size() == M)
                    return;
            }
        }
    }

    int calc(const int C, const int M, const int N)
    {

        //map<long long, long long> products;
        set<long long> products;
        vector<long long> v;

        if (1 == N) return 0;

        calcVector(C, M, N, v, products);

        //for (int i = 0; i < v.size() - 1; i++){
        //    for (int j = 0; j < v.size(); j++)
        //    {
        //        long long i = v[i] * v[j];
        //        products.insert(i);
        //    }
        //}
        //map<long long, long long> result;
        set<long long> result;
        for (auto it : products)
        {
            long long i = it;
            result.insert(i % M);
        }
        
        int count = 0;
        for (auto it : result)
        {
            count++;
        }

        return count;
    }


    void run(istream & in)
    {
        vector<int> v = readInts(in, ' ', 3);
        cout << calc(v[0], v[1], v[2]) << endl;
    }


    virtual void test()
    {
        ifstream in("a.in");
        run(in);
    }
};
