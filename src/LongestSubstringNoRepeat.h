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

    int lengthOfLongestSubstring2(string s) {
        vector<int> map(128, 0);
        int counter = 0, begin = 0, end = 0, d = 0;
        while (end<s.size()) {
            if (map[s[end++]]++>0) counter++;
            while (counter>0) if (map[s[begin++]]-->1) counter--;
            d = max(d, end - begin); //while valid, update d
        }
        return d;
    }

    virtual void test()
    {
        assert(3 == lengthOfLongestSubstring2("abcabcbb"));
        assert(1 == lengthOfLongestSubstring2("bbbbb"));
        assert(3 == lengthOfLongestSubstring2("pwwkew"));  
    }
};
