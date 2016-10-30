#include "Solution.h"

using namespace std;

class LongestSubstringKRepeat: public  solution {

public:

    int longestSubstring(string s, int k, szt p, szt q) {
        szt n = q - p;
        if (n < k)
            return 0;

        szt maxLen = 0;
        vt<int> map(128, 0);
        szt start = 0, end = 0, counter = 0;
        for (szt i = p; i < q; i++)
        {
            map[s[i]]++;
        }

        vt<int> breakPoints;
        for (szt i = p; i < q; i++)
        {
            if (map[s[i]] < k) breakPoints.push_back(i);
        }

        szt i = p;
        szt j = 0;
        szt m = breakPoints.size();

        if (m == 0)
            return (int)n;

        while (i < q)
        {
            while (i < q && j < m && i == breakPoints[j])
            {
                i++; j++;
            }
            szt start = i;
            szt end = i;
            while (i++ < q)
            {
                end = i;
                if ((j < m && i == breakPoints[j]))
                {
                    break;
                }
            }
            if (end != start)
            {

                szt len = longestSubstring(s, k, start, end);
                maxLen = std::max(len, maxLen);
            }
        }

        return (int) maxLen;
    }

    int longestSubstring(string s, int k) {
        return longestSubstring(s, k, 0, s.size());
    }

    int longestSubstring2(string s, int k)
    {
        szt maxLen = 0;
        szt n = s.size();

        if (k > n) return 0;

        for (szt i = 0; i <= n - k;)
        {
            vt<int> m(26, 0);
            int mask = 0;
            int next_i = i + 1;
            // will check substring [i, j]
            for(szt j = i; j < n; j++)
            {
                int cur = s[j] - 'a';
                m[cur]++;
                if (m[cur] < k)
                {
                    mask |= (1 << cur);
                }
                else
                {
                    mask &= ~(1 << cur);
                }

                if (mask == 0)
                {
                    szt len = j - i + 1;
                    //maxLen = std::max(maxLen, len);
                    if (maxLen < len)
                    {
                        maxLen = len;
                        next_i = j + 1;
                    }
                }
            }
            i = next_i;
        }
         
        return (int)maxLen;
    }

    virtual void test()
    {
        assert(3  == longestSubstring2("aaabb", 3));
        assert(5  == longestSubstring2("ababbc",2));
        assert(5  == longestSubstring2("xababbc", 2));
        assert(0  == longestSubstring2("xabcabbc", 3));
        assert(3  == longestSubstring2("abc", 0));
        assert(0  == longestSubstring2("abc", 5));
        assert(15 == longestSubstring2("aaabbbcdefcdefgggggggggggggggcde", 3));
        string a = "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa";
        assert((int)a.size() ==  longestSubstring(a, 1));

    }
};
