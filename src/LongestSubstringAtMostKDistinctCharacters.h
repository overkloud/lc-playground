#include "Solution.h"

using namespace std;

class LongestSubstringAtMostKDistinctCharacters: public  solution {

public:

    int lengthOfLongestSubstringKDistinct(const string &s, int k) {
        szt result = 0;

        if (s.size() > k && s.empty() == false)
        {
            vint dict (256, 0);
            int count = 0;
            szt i = 0, j = 0;
            while (j < s.size())
            {
                if (dict[s[j]] == 0)
                {
                    count++;
                }
                dict[s[j]]++;
                if (count <= k)
                {
                    result = std::max(result, j - i + 1);
                }
                j++;
                while (count > k && i < s.size())
                {
                    dict[s[i]]--;
                    if (dict[s[i]] == 0)
                    {
                        count--;
                    }
                    i++;
                }
            }
        }
        else
        {
            result = s.size();
        }

        return (int)result;
    }

    virtual void test()
    {
        string s = "eceba";
        assert(3 == lengthOfLongestSubstringKDistinct(s, 2));
        assert(1 == lengthOfLongestSubstringKDistinct(s, 1));
        assert(0 == lengthOfLongestSubstringKDistinct(s, 0));
        assert(0 == lengthOfLongestSubstringKDistinct("", 2));
        assert(2 == lengthOfLongestSubstringKDistinct("aa", 2));

        s = "aabcccc";
        assert(7 == lengthOfLongestSubstringKDistinct(s, 3));
        assert(5 == lengthOfLongestSubstringKDistinct(s, 2));
        assert(4 == lengthOfLongestSubstringKDistinct(s, 1));
        assert(0 == lengthOfLongestSubstringKDistinct(s, 0));
    }
};
