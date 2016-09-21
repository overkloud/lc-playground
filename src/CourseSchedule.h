#include "Solution.h"

using namespace std;

class CourseSchedule: public  solution {

public:

    bool canFinish(int n, vector<pair<int, int>>& prerequisites) {
        bool result = true;
        vint visited (n, 0);
        vt<vint> v(n, vint());
        // convert to adj-list
        for (auto edge : prerequisites)
        {
            v[edge.first].push_back(edge.second);
        }

        // dfs on the graph
        for (int i = 0; i < n; i++)
        {
            //map<int,int>path;
            set<int>path;
            queue<int> q;
            vint dep(n, 0);
            if (0 == visited[i])
            {
                q.push(i);
                dep[i] = 0;
                int lastDep = -1;
                while (q.empty() == false)
                {
                    auto node = q.front(); q.pop();
                    if (!visited[node])
                    {
                        visited[node] = 1;

                        // remove previous path to the current dep;
                        if (dep[node] <= lastDep)
                        {
                            for (auto it = path.begin(); it != path.end();)
                            {
                                if (dep[*it] >= dep[node])
                                {
                                    it = path.erase(it);
                                }
                                else ++it;
                            }
                        }
                        lastDep = dep[node];
                        path.emplace(node);
                        for (auto child : v[node])
                        {
                            if (path.find(child) != path.end())
                            {
                                result = false;
                                break;
                            }
                            if (!visited[child] && dep[child] == 0)
                            {
                                q.push(child);
                                dep[child] = dep[node] + 1;
                            }
                        }
                    }
                }
            }
        }

        return result;
    }

    virtual void test()
    {
        vt<pair<int, int>> v5 = { mkp(1,0) };
        auto r5 = canFinish(2, v5);
        assert(r5);

        vt<pair<int, int>> v0 = { mkp(0,0) };
        auto r0 = canFinish(1, v0);
        assert(!r0);

        vt<pair<int,int>> v1 = { mkp(0,1) };
        auto r1 = canFinish(2, v1);
        assert(r1);

        vt<pair<int, int>> v2 = { mkp(0,1), mkp(1,0) };
        auto r2 = canFinish(2, v2);
        assert(!r2);

        vt<pair<int, int>> v3 = { mkp(0,1), mkp(2,0), mkp(3,4), mkp(4,5),mkp(5,3) };
        auto r3 = canFinish(6, v3); 
        assert(!r3);

        vt<pair<int, int>> v4 = { mkp(0,1), mkp(0,2), mkp(1,2) };
        auto r4 = canFinish(3, v4); 
        assert(r4);
    }
};
