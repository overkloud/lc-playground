#include "Solution.h"

using namespace std;

class MinWindow : public  solution {

public:
    string minWindow(string s, string t) 
    {
        string result = "";
        vt<int> dict(256, 0);

        for (auto ch : t)
        {
            dict[ch]++;
        }

        szt start = 0, end = 0, counter, minLen;
        szt n = s.size();
        minLen = n + 1;
        szt begin = 0;
        counter = t.size();

        while (end < n)
        {
            char endCh = s[end];
            if (dict[endCh] > 0)
            {
                counter--;
            }
            end++;
            dict[endCh]--;
            
            while (counter == 0)
            {
                szt len = end - start;
                if (len < minLen)
                {
                    minLen = len;
                    begin = start;
                }
                char startCh = s[start];
                dict[startCh]++;
                if (dict[startCh] > 0)
                {
                    counter++;
                }
                start++;
            }
        }


        if (minLen < n + 1)
        {
            result = s.substr(begin, minLen);
        }
        return result;
    }


    virtual void test()
    {
        auto r = minWindow("aa", "a");
        assert(r == "a");
        r = minWindow("a", "a");
        assert(r == "a");
        auto r2 = minWindow("ADOBECODEBANC", "ABC");
        assert(r2 == "BANC");
        auto r3 = minWindow("CADOBECODEBANC", "ABCX");
        assert(r3 == "");
        auto r4 = minWindow("CADOBECODEBANC", "ABC");
        assert(r4 == "BANC");
        auto r5 = minWindow("DADOBECODEBANC", "ABC");
        assert(r5 == "BANC");
        auto r8 = minWindow("DADOBECODEBANC", "ABCC");
        assert(r8 == "CODEBANC");
        auto r6 = minWindow("DABCBECODEBANC", "ABC");
        assert(r6 == "ABC");
        
        ifstream in("a.in");
        string s, t;
        getline(in, s);
        getline(in, t);
        testUtil::timer t1;
        t1.start();
        auto r7 = minWindow(s, t);
        cout << t1.stop() << endl;
    }
};
