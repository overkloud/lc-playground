#include "Solution.h"

using namespace std;

class LongestSubstringNoRepeat: public  solution {

public:

    int lengthOfLongestSubstring(string s) {
        szt maxLen = 0;
        szt start = 0, end = 0;
        vt<int> map(256, 0);
        szt n = s.size();

        while (end < n)
        {
            char endCh = s[end];
            if (map[endCh] == 0)
            {
                map[endCh]++;
                end++;
                szt len = end - start;
                maxLen = std::max(maxLen, len);
            }
            else
            {
                char startCh = s[start];
                map[startCh]--;
                start++;
            }

        }

        return maxLen;
    }


    virtual void test()
    {
        assert(3 == lengthOfLongestSubstring("abcabcbb"));
        assert(1 == lengthOfLongestSubstring("bbbbb"));
        assert(3 == lengthOfLongestSubstring("pwwkew"));  
    }
};
