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

    int calc2(vector<vector<int>> &R, const int M)
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


    struct pos
    {
        ll a;
        ll b;
        ll cost;

        pos(ll a, ll b, ll cost )
        {
            this->a = min(a, b);
            this->b = max(a, b);
            this->cost = cost;
        }

        long long  s()
        {
            return getKey(a, b);
        }

        static long long getKey(ll a, ll b)
        {
            ll i = min(a, b);
            ll j = max(a, b);
            long long key = a << 8 | b;
            return key;
        }
    };

    ll calc_help(vector<vector<int>> & v)
    {
        vector<map<long long, pos*>> cost;
        for (int i = (int)v.size() - 1; i >= 0; i--)
        {
            auto it = v[i];
            int in = it[0];
            int out = it[1];
            map<long long, pos*> m;
            if (i == v.size() - 1)
            {
                pos*s = new pos(i, -1, 0);
                m.emplace(s->s(), s);
                cost.push_back(m);
            }
            else if (i == v.size() - 2)
            {
                pos* s = new pos(i, i + 1, 0);
                m.emplace(s->s(), s);

                pos* s2 = new pos(i, -1, abs(out - v[i+1][0]));
                m.emplace(s2->s(), s2);
                cost.push_back(m);
            }
            else
            {
                for (auto j : cost[v.size() - 2 - i])
                {
                    auto p = j.second;
                    if (p->a == -1)
                    {
                        pos * p1 = new pos(i, -1, abs(out - v[p->b][0]) + p->cost);
                        m.emplace(p1->s(), p1);

                        pos *p2 = new pos(i, p->b, p->cost);
                        m.emplace(p2->s(), p2);
                    }
                    else
                    {
                        int dist_a = abs(out - v[p->a][0]);
                        int dist_b = abs(out - v[p->b][0]);

                        long long ka = pos::getKey(i, p->b);
                        if (m.find(ka) != m.end())
                        {
                            auto it = m.find(ka);
                            if (it->second->cost > p->cost + dist_a)
                                it->second->cost = p->cost + dist_a;
                        }
                        else {
                            pos * pa = new pos(i, p->b, p->cost + dist_a);
                            m.emplace(pa->s(), pa);
                        }

                        long long kb = pos::getKey(i, p->a);
                        if (m.find(kb) != m.end())
                        {
                            auto it = m.find(kb);
                            if (it->second->cost > p->cost + dist_b)
                                it->second->cost = p->cost + dist_b;
                        }
                        else {
                            pos * pb = new pos(i, p->a, p->cost + dist_b);
                            m.emplace(pb->s(), pb);
                        }
                    }
                }
                cost.push_back(m);
            }
        }

        ll min = -1;
        auto x = cost.back();
        for (auto i : x)
        {
            if (min == -1)
                min = i.second->cost;
            else if (min > i.second->cost)
                min = i.second->cost;
        }

        return min;
    }

    ll calc(vector<vector<int>> v, const int M)
    {
        ll sum = 0;
        for (auto i : v)
        {
            sum += abs(i[1] - i[0]);
        }

        sum = sum + calc_help(v);
        
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
