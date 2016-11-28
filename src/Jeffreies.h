#include "Solution.h"

using namespace std;

class Jeffreies: public  solution {

public:

    /*
    * Complete the function.
    */
    int validateBrackets(const std::string& str)
    {
        set<char> open = {'{', '(','['};
        set<char> close = { '}', ')',']' };
        unordered_map<char, char> m;
        m.emplace('(', ')');
        m.emplace('[', ']');
        m.emplace('{', '}');

        stack<char> ss;
        for (auto c : str)
        {
            if (open.count(c))
            {
                ss.push(c);
            }
            else if (close.count(c))
            {
                if (ss.empty()) return -1;
                char prev = ss.top(); ss.pop();
                if (m[prev] != c)
                {
                    return -1;
                }
            }
        }

        return ss.empty() ? 0 : -1;
    }

    /*
    * Complete the function.
    */

    void calc(vint & arr, const int k, vint & v)
    {
        if (k == 1)
        {
            range(arr.size())
            {
                v[i] = arr[i];
            }
        }
        else
        {
            vint v_p(arr.size()-k+2,INT_MAX);
            calc(arr, k - 1, v_p);
            for (int i = 0; i < arr.size()-k + 1; i++)
            {
                v[i]=(std::min(arr[i + k - 1], v_p[i]));
            }
        }
    }


    int segment_slow(vector < int >& arr, int k)
    {
        if (arr.size() == 0 || k <= 0) return 0;

        if (k >= arr.size())
        {
            return *std::min_element(arr.begin(), arr.end());
        }

        vint v(arr.size()-k+1, INT_MAX);
        calc(arr, k, v);
        return *std::max_element(v.begin(), v.end());
    }

    int segment(vector < int >& arr, int k)
    {
        if (arr.size() == 0 || k <= 0) return 0;

        if (k >= arr.size())
        {
            return *std::min_element(arr.begin(), arr.end());
        }

        return fast_sol(arr, k);
    }

    int fast_sol(vint & v, const int k)
    {
        const int n = v.size();
        vint left(n + 1, -1);
        vint right(n + 1, n);

        stack<int> ss;
        range(n)
        {
            while (!ss.empty() && v[ss.top()] >= v[i])
                ss.pop();

            if (!ss.empty())
                left[i] = ss.top();

            ss.push(i);
        }
        stack<int>sss;
        ss.swap(sss);
        // do something similar to right
        for (int i = n - 1; i >= 0; i--)
        {
            while (!ss.empty() && v[ss.top()] >= v[i])
                ss.pop();

            if (!ss.empty())
                right[i] = ss.top();

            ss.push(i);
        }

        vint res(n + 1, 0);
        range(n)
        {
            auto ls = right[i] - left[i] - 1;
            res[ls] = max(res[ls], v[i]);
        }
        for (int i = n - 1; i >= 1; i--)
        {
            res[i] = max(res[i], res[i + 1]);
        }
        return res[k];
    }

    virtual void test()
    {
        /*assert(validateBrackets("{}[]()") == 0);
        assert(validateBrackets("{{])") == -1);
        assert(validateBrackets("{{}}}") == -1);
        assert(validateBrackets("{{}}") == 0);
        assert(validateBrackets("{}}") == -1);
        assert(validateBrackets("aaaa{a}a[aaa]a(aa{1!@#aaaa})a#!@3") == 0);*/
        vint v1 = {1,2,3,1,2};
        assert(3 == segment(v1, 1));
        assert(1 == segment(v1, 3));
        assert(1 == segment(v1, 10));

        vint v2 = { 1,1,1 };
        assert(1 == segment(v2, 2));

        vint v3 = {2,5,4,6,8};
        assert(4 == segment(v3, 3));

        testUtil::timer t1;
        t1.start();
        vint v4 = testUtil::randomGen(2000, 50, false);
        //vint v4 = { 49,2,18,10,45,1,13,3,29,26,5,22,48,49,41,23,22,0,40,19 };
        auto r4 = segment(v4, 500);
        cout << t1.stop() << endl;
        t1.reset();
        auto r5 = segment_slow(v4, 500);
        assert(r4 == r5);
        cout << t1.stop() << endl;

    }
};
