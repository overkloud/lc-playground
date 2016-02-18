#include "Solution.h"

using namespace std;

class TwoRobots: public  solution {

public:

    struct routine
    {
        int cost;
        int in;
        int out;

        routine(int i, int o, int c)
        {
            cost = c;
            in = i;
            out = o;
        }
    };

    int calc(vector<vector<int>> &R, const int M)
    {
        set<int> ins;
        set<int> outs;

        int sum = 0;
        for (auto i : R)
        {
            sum += abs(i[1] - i[0]);
        }


        if (R.size() <= 2) return sum;

        
        auto cmp = [](routine* a, routine* b){
            return a->cost < b->cost;
        };
        //priority_queue<routine*, vector<routine*>, decltype(cmp)> queues (cmp);

        vector<routine*> queues;

        for (int i = 0; i < R.size() - 1; i++)
        {
            int out = R[i][1];
            for (int j = i + 1; j < R.size(); j++)
            {
                int in = R[j][0];
                int cost = abs(out - in);
                routine * rp = new routine(j, i, cost);
                queues.push_back(rp);
            }
        }

        sort(queues.begin(), queues.end(), cmp);

        int runs = 0;
        int i = 0;
        while (runs < R.size() - 2)
        {
            auto minEdge = queues[i];
            i++;
            int min = minEdge->cost;
            int in = minEdge->in;
            int out = minEdge->out;

            if (ins.find(in) == ins.end() && outs.find(out) == outs.end())
            {
                ins.insert(in);
                outs.insert(out);
                sum += min;
                runs++;
            }
        }

        return sum;
    }

    void run(istream & in)
    {
        string line;
        getline(in, line);
        int T = atoi(line.c_str());

        for (int i = 0; i < T; i++)
        {
            vector<int> v1 = readInts(in, ' ', 2);
            int M = v1[0];
            int N = v1[1];
            vector<vector<int>> routines;
            for (int i = 0; i < N; i++)
            {
                routines.push_back(readInts(in, ' ', 2));
            }
            cout << calc(routines, M) << endl;
        }
    }

    virtual void test()
    {
        ifstream in("a.in");
        run(in);
    }
};
