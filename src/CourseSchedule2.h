#include "Solution.h"

using namespace std;

class CourseSchedule2: public  solution {

public:

    vector<int> findOrder(int n, vector<pair<int, int>>& prerequisites) {
        vint result;
        vt<vint> v(n,vint());
        vint pre(n,0);
        for (auto e : prerequisites)
        {
            v[e.second].push_back(e.first);
            pre[e.first]++;
        }

        vint visited(n,0);
        stack<int> s;
        range(pre.size())
        {
            if (pre[i] == 0)
                s.push(i);
        }
        while (!s.empty())
        {
            auto node = s.top(); s.pop();
            if (1 != visited[node])
            {
                visited[node] = 1;
                result.push_back(node);
                for (auto child : v[node])
                {
                    pre[child]--;
                    if (!visited[child] && pre[child] == 0)
                    {
                        s.push(child);
                    }
                }
            }
        }

        if (result.size() != n)
        {
            result = vint();
        }

        return result;
    }

    virtual void test()
    {
        vt<pair<int, int>> v5 = { mkp(1,0) };
        auto r5 = findOrder(2, v5);
        assert(r5.size() == 2);

        vt<pair<int, int>> v0 = { mkp(0,0) };
        auto r0 = findOrder(1, v0);
        assert(r0.size() == 0);

        vt<pair<int, int>> v1 = { mkp(0,1) };
        auto r1 = findOrder(2, v1);
        assert(r1.size() == 2);

        vt<pair<int, int>> v2 = { mkp(0,1), mkp(1,0) };
        auto r2 = findOrder(2, v2);
        assert(r2.size() == 0);

        vt<pair<int, int>> v3 = { mkp(0,1), mkp(2,0), mkp(3,4), mkp(4,5),mkp(5,3) };
        auto r3 = findOrder(6, v3);
        assert(r3.size() == 0);

        vt<pair<int, int>> v4 = { mkp(0,1), mkp(0,2), mkp(1,2) };
        auto r4 = findOrder(3, v4);
        assert(r4.size() == 3);

        vt<pair<int, int>> v6 = {};
        auto r6 = findOrder(5, v6);
        assert(r6.size() == 5);
    }
};
