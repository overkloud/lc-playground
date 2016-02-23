#include "Solution.h"

using namespace std;

class CountSort: public  solution {

public:

    map<int, int> countSort1(vector<int> v)
    {
        map<int, int> M;
        for (int i : v)
        {
            auto it = M.find(i);
            if (it == M.end())
            {
                M.insert(make_pair(i, 1));
            }
            else
            {
                it->second++;
            }
        }

        for (int i = 0; i < 100; i++)
        {
            auto it = M.find(i);
            if (it == M.end())
            {
                cout << 0 << " ";
            }
            else
            {
                cout << it->second << " ";
            }
        }

        return M;
    }

    void countSort2(vector<int> v)
    {
        map<int, int> M;
        int min, max;

        if (v.size() == 0) return;
        min = max = v[0];
        for (int i : v)
        {
            auto it = M.find(i);
            if (it == M.end())
            {
                M.insert(make_pair(i, 1));
            }
            else
            {
                it->second++;
            }
            if (min > i) min = i;
            if (max < i) max = i;
        }

        for (int i = min; i <= max; i++)
        {
            auto it = M.find(i);
            if (it != M.end())
            {
                auto k = it->second;
                for (int j = 0; j < k; j++)
                {
                    cout << i << " ";
                }
            }
        }
    }

    void countSort3(vector<int> & v)
    {
        map<int, int> M;
        int min, max;

        if (v.size() == 0) return;
        min = max = v[0];
        for (int i : v)
        {
            auto it = M.find(i);
            if (it == M.end())
            {
                M.insert(make_pair(i, 1));
            }
            else
            {
                it->second++;
            }
            if (min > i) min = i;
            if (max < i) max = i;
        }

        int sum = 0;
        for (int i = 0; i < 100; i++)
        {
            auto it = M.find(i);
            if (it == M.end())
            {

            }
            else
            {
                sum += it->second;
            }
            cout << sum << " ";
        }
    }

    struct CountSortItem
    {
        CountSortItem(int i, string &s)
        {
            this->i = i;
            this->s = s;
        }
        int i;
        string s;
    };

    void countSort(vector<CountSortItem> & v)
    {
        const static int RANGE = 100;
        int M[RANGE];
        std::function <int()> initInt = [](){ return 0; };
        initArray<int>(M, RANGE, initInt);
        for (auto item : v)
        {
            M[item.i]++;
        }

        int C[RANGE];
        initArray<int>(C, RANGE, initInt);
        for (int i = 1; i < RANGE; i++)
        {
            C[i] = M[i - 1] + C[i - 1];
        }

        szt size = v.size();
        int count = 0;
        const string placeholder = "-";
        vector<string> results (size, "");
        for (CountSortItem i : v)
        {
            int index = C[i.i];
            if (count < size / 2)
            {
                count++;
                results[index] = placeholder;
            }
            else
            {
                count++;
                results[index] = i.s;
            }
            C[i.i]++;
        }

        for (auto s : results)
        {
            cout << s << " ";
        }
        cout << endl;
    }

    void run(istream & in)
    {
        int count;
        string line;
        getline(in, line);
        count = atoi(line.c_str());

        //vector<int> ints = readInts(in);
        vector<CountSortItem> v;
        while (getline(in, line))
        {
            vector<string> splits = split(line);
            int i = (atoi(splits[0].c_str()));
            CountSortItem item(i, splits[1]);
            v.push_back(item);
        }
        countSort(v);
    }

    virtual void test()
    {
        ifstream in("a.in");
        run(in);
    }
};
